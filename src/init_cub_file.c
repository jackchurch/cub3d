#include <fcntl.h>

#include "../inc/map.h"
#include "cub_file.h"
#include "constance.h"
#include "cub3d.h"

char	**reallocate(char ***old, int i)
{
	char	**new;
	int		j;

	j = -1;
	new = malloc(sizeof(char *) * (i + 2));
	while (++j < i)
		new[j] = (*old)[j];
	free(*old);
	return (new);
}

void	*ft_realloc(void *ptr, size_t old_len, size_t new_len)
{
	void *new_ptr;

	if (new_len == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_len));
	if (new_len <= old_len)
		return (ptr);
	new_ptr = malloc(new_len);
	if (new_ptr)
	{
		ft_memcpy(new_ptr, ptr, old_len);
		free(ptr);
	}
	return (new_ptr);
}

int	is_only_one(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (is_white_space(line[i]) || line[i] == '1')
			i++;
		else
			return (0);
	}
	return (1);
}

/*
Return element type only if element has a space or tab after the last valid char.
ie C345,654,344 will fail.
C   645,421,334 will pass
*/
int	discover_element_type(char *current_line)
{ 
	char	*line;

	if (is_only_one(current_line))
		return (MAP);
	// On this line, remove leading and tailing spaces and tabs (this will need not happen for the map part)
	line = ft_strtrim(current_line, " 	");
	if (line[0] == 'C' && is_white_space(line[1]))
		return (CEILING);
	else if (line[0] == 'F' && is_white_space(line[1]))
		return (FLOOR);
	else if (line[0] == 'N' && line[1] == 'O' && is_white_space(line[2]))
		return (NORTH);
	else if (line[0] == 'S' && line[1] == 'O' && is_white_space(line[2]))
		return (SOUTH);
	else if (line[0] == 'E' && line[1] == 'A' && is_white_space(line[2]))
		return (EAST);
	else if (line[0] == 'W' && line[1] == 'E' && is_white_space(line[2]))
		return (WEST);
	return (-1);
}

/*Remove the C or F from the return string and then remove any leading white space.*/
char	*isolate_element_path(char *str, int i)
{
	char	*temp;
	char	*ret;
	
	temp = ft_substr(str, i, ft_strlen(str));
	ret = ft_strtrim(str, " 	");
	free(temp);
	free(str);
	return (ret);
}

int	init_map(t_map *map, char *line)
{
	int		length;
	int		j;
	int		i;

	length = ft_strlen(line);
	i = map->rows;
	printf("rows: %d\n", map->rows);
	if (!map->content)
		map->content = malloc(sizeof(char *));
	else
		map->content = ft_realloc(map->content, i * sizeof(char *), (i + 1) * sizeof(char *));
	length = ft_strlen(line);
	if (length > map->longest_row)
	{
		while (j < i)
		{
			map->content[j] = ft_realloc(map->content[j], map->longest_row, length + 1);
			ft_memset(map->content[j] + map->longest_row, 32, length - map->longest_row + 1);
			j++;
		}
		map->longest_row = length;
	}
	map->content[i] = malloc(length + 1);
	j = 0;
	while (j < length)
	{
		map->content[i][j] = line[j];
		j++;
	}
	map->content[i][j] = '\0';
	map->rows++;
	return (1);
}

int	do_shit(t_input *input, char *current_line)
{
	char	*str_1;

	printf("Current Line: %s\n", current_line);
	str_1 = ft_strdup(current_line);
	if (input->map.loading_map == false)
		input->element_type = discover_element_type(str_1);
	if (input->element_type == -1)
		return (-1);
	if (input->element_type == MAP)
	{
		if (input->map.loading_map == false)
			input->map.loading_map = true;
		init_map(&input->map, current_line);
	}
	else if (input->element_type != CEILING && input->element_type != FLOOR)
		ceiling_floor_branch(input, str_1, input->element_type);
	else
		ceiling_floor_branch(input, str_1, input->element_type);
	return (0);
}


t_input	init_cub_file(char *file_name)
{
	int		fd;
	char	*current_line;
	t_input input;

	ft_memset(&input, 0, sizeof(t_input));
	ft_memset(&input.map, 0, sizeof(t_map));
	input.map.loading_map = false;
	fd = open_cub_file(file_name);
	current_line = get_next_line(fd);
	while (current_line != NULL)
	{
		while (current_line[0] == '\n')
			current_line = get_next_line(fd);
		if (input.map.loading_map == true && is_only_one(current_line))
			input.map.loading_map = false;
		do_shit(&input, current_line);
		current_line = get_next_line(fd);
	}
	free(current_line);
	close(fd);
	return (input);
}

/*
AddressSanitizer:DEADLYSIGNAL
=================================================================
==10873==ERROR: AddressSanitizer: SEGV on unknown address (pc 0x7ff86ec28b46 bp 0xbebebebebebebebe sp 0x7ffefaefd700 T0)
==10873==The signal is caused by a READ memory access.
==10873==Hint: this fault was caused by a dereference of a high value address (see register values below).  Dissassemble the provided pc to learn which register was used.
    #0 0x7ff86ec28b46 in bool __sanitizer::atomic_compare_exchange_strong<__sanitizer::atomic_uint8_t>(__sanitizer::atomic_uint8_t volatile*, __sanitizer::atomic_uint8_t::Type*, __sanitizer::atomic_uint8_t::Type, __sanitizer::memory_order) ../../../../src/libsanitizer/sanitizer_common/sanitizer_atomic_clang.h:80
    #1 0x7ff86ec28b46 in __asan::Allocator::AtomicallySetQuarantineFlagIfAllocated(__asan::AsanChunk*, void*, __sanitizer::BufferedStackTrace*) ../../../../src/libsanitizer/asan/asan_allocator.cpp:621
    #2 0x7ff86ec28b46 in __asan::Allocator::Deallocate(void*, unsigned long, unsigned long, __sanitizer::BufferedStackTrace*, __asan::AllocType) ../../../../src/libsanitizer/asan/asan_allocator.cpp:697
    #3 0x7ff86ec28b46 in __asan::asan_free(void*, __sanitizer::BufferedStackTrace*, __asan::AllocType) ../../../../src/libsanitizer/asan/asan_allocator.cpp:971
    #4 0x7ff86ecb44f4 in __interceptor_free ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:128
    #5 0x56414888cca2 in safe_exit src/main.c:41
    #6 0x56414888d648 in key_hook src/ft_mlx.c:30
    #7 0x564148894f45 in mlx_loop (/home/reuben/Desktop/cub3d/a.out+0xbf45)
    #8 0x56414888d31f in main src/main.c:114
    #9 0x7ff86e629d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #10 0x7ff86e629e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #11 0x56414888c9c4 in _start (/home/reuben/Desktop/cub3d/a.out+0x39c4)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV ../../../../src/libsanitizer/sanitizer_common/sanitizer_atomic_clang.h:80 in bool __sanitizer::atomic_compare_exchange_strong<__sanitizer::atomic_uint8_t>(__sanitizer::atomic_uint8_t volatile*, __sanitizer::atomic_uint8_t::Type*, __sanitizer::atomic_uint8_t::Type, __sanitizer::memory_order)
==10873==ABORTING
*/
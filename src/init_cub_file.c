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
	new = malloc(sizeof(char *) * (i + 1));
	while (++j < i)
		new[j] = (*old)[j];
	free(*old);
	return (new);
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
		reallocate(&map->content, i);
	length = ft_strlen(line);
	if (length > map->longest_row)
		map->longest_row = length;
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
	if (input->map.loading_map < 0)
		input->element_type = discover_element_type(str_1);
	if (input->element_type == -1)
		return (-1);
	if (input->element_type == MAP)
	{
		if (input->map.loading_map < 0)
			input->map.loading_map *= -1;
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
	input.map.loading_map = -1;
	fd = open_cub_file(file_name);
	current_line = get_next_line(fd);
	while (current_line != NULL)
	{
		while (current_line[0] == '\n')
			current_line = get_next_line(fd);
		if (input.map.loading_map == 1 && is_only_one(current_line))
			input.map.loading_map *= -1;
		do_shit(&input, current_line);
		current_line = get_next_line(fd);
	}
	close(fd);
	return (input);
}

/*
=================================================================
==10701==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x602000000378 at pc 0x5567320ce880 bp 0x7ffcb6181f30 sp 0x7ffcb6181f20
WRITE of size 8 at 0x602000000378 thread T0
    #0 0x5567320ce87f in init_map src/init_cub_file.c:93
    #1 0x5567320cec1f in do_shit src/init_cub_file.c:119
    #2 0x5567320cef37 in init_cub_file src/init_cub_file.c:146
    #3 0x5567320c8073 in main src/main.c:99
    #4 0x7f4040a29d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #5 0x7f4040a29e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #6 0x5567320c79c4 in _start (/home/reuben/Desktop/cub3d/a.out+0x39c4)

0x602000000378 is located 0 bytes to the right of 8-byte region [0x602000000370,0x602000000378)
freed by thread T0 here:
    #0 0x7f4040eb4537 in __interceptor_free ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:127
    #1 0x5567320ce01e in reallocate src/init_cub_file.c:17
    #2 0x5567320ce7be in init_map src/init_cub_file.c:89
    #3 0x5567320cec1f in do_shit src/init_cub_file.c:119
    #4 0x5567320cef37 in init_cub_file src/init_cub_file.c:146
    #5 0x5567320c8073 in main src/main.c:99
    #6 0x7f4040a29d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

previously allocated by thread T0 here:
    #0 0x7f4040eb4887 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x5567320ce7a1 in init_map src/init_cub_file.c:87
    #2 0x5567320cec1f in do_shit src/init_cub_file.c:119
    #3 0x5567320cef37 in init_cub_file src/init_cub_file.c:146
    #4 0x5567320c8073 in main src/main.c:99
    #5 0x7f4040a29d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

SUMMARY: AddressSanitizer: heap-buffer-overflow src/init_cub_file.c:93 in init_map
Shadow bytes around the buggy address:
  0x0c047fff8010: fa fa 00 00 fa fa 00 04 fa fa 00 00 fa fa 00 04
  0x0c047fff8020: fa fa 00 00 fa fa fd fd fa fa 00 07 fa fa 00 04
  0x0c047fff8030: fa fa fd fd fa fa fd fd fa fa 07 fa fa fa 03 fa
  0x0c047fff8040: fa fa 05 fa fa fa 07 fa fa fa fd fd fa fa 00 00
  0x0c047fff8050: fa fa 00 04 fa fa fd fd fa fa fd fd fa fa 00 fa
=>0x0c047fff8060: fa fa 04 fa fa fa 04 fa fa fa 00 fa fa fa fd[fa]
  0x0c047fff8070: fa fa 00 00 fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff8080: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff8090: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff80a0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff80b0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc
==10701==ABORTING*/
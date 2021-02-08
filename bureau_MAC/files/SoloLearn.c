#include <stdio.h>
#include <stdlib.h>

//link youtube
char *len(char *str)
{
    char *rtn;
    int i = 0,j = 0;
    while(str[i])
        i++;
    j = i;
    while(str[i] != '=' && str[i] != '/' && i != 0)
        i--;
	if (str[i] != '=' && str[i] != '/')
		return "NULL";
    rtn = malloc(sizeof(char*) * j - i);
    j = 0;
    while (str[++i])
    {
        rtn[j] = str[i];
        j++;
    }
    // printf("%s\n", rtn);
	return rtn;
}
int	ft_count(char * str)
{
	int count;

	count = 0;
	while (*str++ != '\0')
		if ((*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z') || *str == ' ')
			count++;
	return (count);
}
//get word nd reverse       ft_count
char *get_word(char *str)
{
	char *rtn;
	char tmp;
	int i;
	int j;

	i = -1;
	j = 0;
	rtn = malloc(ft_count(str) + 1);
	while (str[++i] != '\0')
		if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || str[i] == ' ')
			rtn[j++] = str[i];
	rtn[j--] = '\0';
	i = -1;
	while (++i < j / 2)
	{
		tmp = rtn[i];
		rtn[i] = rtn[j - i];
		rtn[j - i] = tmp;
	}
	return rtn;
}
//check password
int	check_symole(char * str)
{
	while (*str++)
	{
		if (*str == '!' || *str == '@' || *str == '#' || *str == '$' || *str == '%' || *str == '&' || *str == '*')
			return 1;
	}
	return 0;
}
void	check_password(char * str)
{
	int letter = 0, number = 0, symbole = 0, i = 0;
	while (*str)
	{
		if ((*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z'))
			letter++;
		else if (*str >= '0' && *str <= '9')
			number++;
		else if (check_symole(str))
			symbole++;
		*str++;
		i++;
	}
	if (i >= 7)
	{
		if (number >= 2 && symbole >= 2)
			printf("Strong\n");
		else
			printf("Weak\n");
	}
}
//no numerals
void	replace_number_to_word(char * str)
{
	char nbr[11][6] = {
		{'z', 'e', 'r', 'o', ' ', ' '},
		{'o', 'n', 'e', ' ', ' ', ' '},
		{'t', 'w', 'o', ' ', ' ', ' '},
		{'t', 'r', 'e', 'e', ' ', ' '},
		{'f', 'o', 'u', 'r', ' ', ' '},
		{'f', 'i', 'v', 'e', ' ', ' '},
		{'s', 'i', 'x', ' ', ' ', ' '},
		{'s', 'e', 'v', 'e', 'n', ' '},
		{'e', 'i', 'g', 'h', 't', ' '},
		{'n', 'i', 'n', 'e', ' ', ' '},
		{'t', 'e', 'n', ' ', ' ', ' '}
		};
	
	char *replace = malloc(100);
	int i = 0, j, r = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			j = 0;
			if (str[i + 1] == '0')
				while (nbr[10][j] != ' ')
					replace[r++] = nbr[10][j++];
			else
			if (str[i - 1] != '1')
				while (nbr[str[i] - 48][j] != ' ')
					replace[r++] = nbr[str[i] - 48][j++];
		}
		else
				replace[r++] = str[i];
		i++;
	}
	printf("%s\n", replace);
}
int main() {
    // char *str = malloc(50);
    // gets(str);
	// check_password(str);
	replace_number_to_word("1only 10.");
    return 0;
}
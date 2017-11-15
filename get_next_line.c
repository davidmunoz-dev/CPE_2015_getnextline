/*
** get_next_line.c for head in /CPE_2015_getnextline
**
** Made by Munoz David
** Login   <munoz_d@epitech.net>
**
** Started on  Mon Jan 11 23:08:46 2016 Munoz David
** Last update Tue Mar  8 11:24:24 2016 David Munoz
*/

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

/*
**	my_gnl_read contient un int "lenght_read" qui correspond
**	au nombre de caractères à lire grâce au
**	read(filedescriptor, buffer, TAILLE_A_LIRE)
**	avec buffer la chaine de caractère
*/
int	my_gnl_read(char *buffer, const int fd, int *i)
{
  int   lenght_read;

  if ((lenght_read = read(fd, buffer, READ_SIZE)) < 0)
    return (-1);
  *i = 0;
  return (lenght_read);
}

/*
**	my_gnl_strcpy contient un char* "destination" qui correspond
**	à la chaine de caractère "source" avec exactement le même
**	nombre de caractères restant
*/
char	*my_gnl_strcpy(char *source, char c, int lenght_line)
{
  char  *destination;
  int   i;

  i = -1;
  if ((destination = malloc(sizeof(char *) * (lenght_line + 10))) == NULL)
    return (NULL);
  while (++i != lenght_line)
    destination[i] = source[i];
  destination[lenght_line] = c;
  if (lenght_line != 0)
    free(source);
  return (destination);
}

/*
**	my_gln_error check s'il reste des caractères à lire
*/
char	*my_gnl_error(char *line, int i, int lenght_read, int lenght_line)
{
  if (lenght_read != READ_SIZE && !line[i - 1] && (i - 1 == lenght_read))
    return (NULL);
  else
    return (my_gnl_strcpy(line, '\0', lenght_line));
}

/*
**	get_next_line est la fonction principale du programme
**	elle retourne une ligne lue dans un file descriptor
**	elle renvoie sont resultat sans le '\n'
**	si elle n'a plus rien à lire elle renvoie (NULL)
*/
char	*get_next_line(const int fd)
{
  static char   buffer[READ_SIZE];
  static int    l_read;
  static int    n;
  char          *line;
  int           l_line;

  l_line = 0;
  line = "";
  if (n == 0)
    l_read = ((l_read = my_gnl_read(buffer, fd, &n)) <= 0) ? 0 : l_read;
  while (l_read != 0)
    {
      if (n == l_read)
        l_read = ((l_read = my_gnl_read(buffer, fd, &n)) <= 0) ? 0 : l_read;
      if (buffer[n] == '\n' || (n == l_read && l_read != READ_SIZE))
        return (line = my_gnl_error(line, ++n, l_read, l_line));
      if ((line = my_gnl_strcpy(line, buffer[n], l_line)) == NULL)
        return (NULL);
      n++;
      l_line++;
    }
  return (NULL);
}

#include "shell.h"

/**
 *  _myhistory - displays the history list, one command by line from recent
 *
 *  Return: = 0 Success
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 *
 *
 * Return: 0 = success, 1 = error
 */
int unset_alias(info_t *info, char *str)
{
	char *pt, c;
	int ret;

	pt = _strchr(str, '=');
	if (!pt)
		return (1);
	c = *pt;
	*pt = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*pt = c;
	return (ret);
}
/**
 * set_alias - sets alias to string
 * Return:  0 = success, 1 = error
 */
int set_alias(info_t *info, char *str)
{
	char *pt;

	pt = _strchr(str, '=');
	if (!pt)
		return (1);
	if (!*++pt)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 *
 * Return:  0 = success, 1 = error
 */
int print_alias(list_t *node)
{
	char *pt = NULL, *a = NULL;

	if (node)
	{
		pt = _strchr(node->str, '=');
		for (a = node->str; a <= pt; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(pt + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *pt = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		pt = _strchr(info->argv[i], '=');
		if (pt)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

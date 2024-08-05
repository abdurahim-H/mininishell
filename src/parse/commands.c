#include "minishell.h"

t_commands *createCommands()
{
	t_commands *newCmd;

	newCmd = (t_commands *) ft_gc_malloc (sizeof(t_commands));
	if (!newCmd)
		return NULL;
	newCmd->cmds = NULL;
	newCmd->heredoc = NULL;
	newCmd->fd_in = 0;
	newCmd->fd_out = 0;
	newCmd->ind = 0;
	newCmd->next = NULL;
	return (newCmd);
}

void fillArgs(t_commands *cmd, Token *token)
{
	cmd->cmds = ft_realloc_char(cmd->cmds, cmd->ind + 2);
	cmd->cmds[cmd->ind] = ft_strdup(token->text);
	cmd->cmds[++cmd->ind] = NULL;
}

int	fillCommands(t_mini *mini, t_commands *cmd, Token *token)
{
	if (token->type == COMMAND)
	{
		return (fillArgs(cmd, token), true);
	}
	else if (token->type == REDIRECT_IN)
	{
		if (token->next->type != COMMAND && token->text == NULL)
			return (syntaxError(mini, findType(token->next->type)), false);
		if (cmd->fd_in)
			close(cmd->fd_in);
		cmd->fd_in = inOpener(token->text);
		if (cmd->heredoc)
			ft_gc_free(cmd->heredoc);
		cmd->heredoc = NULL;
		if (cmd->fd_out == -1)
		{
			mini->exitcode = 1;
			return (false);
		}
	}
	else if (token->type == REDIRECT_OUT)
	{
		if (token->next->type != COMMAND && token->text == NULL)
			return (syntaxError(mini, findType(token->next->type)), false);
		cmd->fd_out = outOpener(token->text);
		if (cmd->fd_out == -1)
		{
			mini->exitcode = 1;
			return (false);
		}
	}
	else if (token->type == REDIRECT_OUT)
	{
		if (token->next->type != COMMAND && token->text == NULL)
			return (syntaxError(mini, findType(token->next->type)), false);
		if (cmd->fd_out)
			close(cmd->fd_out);
		cmd->fd_out = outApendOpener(token->text);
		if (cmd->fd_out == -1)
		{
			mini->exitcode = 1;
			return (false);
		}
	}
	else if (token->type == HEREDOC)
	{
		if (token->next->type != COMMAND && token->text == NULL)
			return (syntaxError(mini, findType(token->next->type)), false);
		cmd->heredoc = ft_strdup(token->text);
	}
	return (true);
}

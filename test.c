# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

int	main(int argc, char **argv)
{
	//save in/out
	int tmpin = dup(0);
	int tmpout = dup(1);	

	//set the initial input
	int fdin;
	if (infile)
		fdin = open(infile, O_RDONLY);
	else
		fdin = dup(tmpin);//Use default input
	
	int ret;
	int fdout;
	for (i = 0; i < numsimplecommands; i++)
	{
		//redirect input
		dup2(fdin, 0);
		close(fdin);
		//set output
		if (i == numsimplecommands - 1)
		{
			//Last simple command
			if (outfile)
				fdout = open(outfile, O_WRONLY);
			else
			{
				// Use default output
				fdout = dup(tmpout);
			}	
		}
		else
		{
			// Not last simple command create pipe
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		// Redirect output
		dup2(fdout, 1);
		close(fdout);

		// Create child process;
		ret = fork();
		if (ret == 0)
		{
			execve(path, str, p->arr_env);
			perror("exe");
			exit(1);
		}
	}
	// restore in/out defaults
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	waitpid(ret, NULL, 0);
	return (0);
}
#!./minishell


echo "I'm a script"
echo "With two commands"
ARG=my_arg
export FOO=bar
wrong_command
echo $ARG
echo $FOO
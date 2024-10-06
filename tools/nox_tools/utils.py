import platform
import subprocess

def find_executable(executable):
    """
    Finds an executable.

    Args:
        executable:
            executable name
    Returns:
        str:
            path to the executable, None if not found
    """
    cmd = "where" if platform.system() == "Windows" else "which"
    return run_command_output(cmd + " " + executable)
    
def run_command_result(command):
    """
    Runs a command and returns the result of that command.

    Args:
        command:
            command to run
    Returns:
        int:
            0 on success, 1 on failure
    """
    print(f'Running [{command}] command', flush=True)
    
    try:
        result = subprocess.run(command, 
                                stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE,
                                shell=True)
    except subprocess.CalledProcessError:
        print(f'{command} failed to run', flush=True)
        return 1
    
    if result.returncode != 0:
        print(result.stdout.decode('utf-8'), flush=True)
        return 1

    print("Success\n")
    return 0

def run_command_output(command):
    """
    Runs a command and returns the output of that command.

    Args:
        command:
            command to run
    Returns:
        str:
            output of the command
    """
    try:
        result = subprocess.check_output(command, shell=True)
    except subprocess.CalledProcessError:
        print(f'[{command}] failed to run', flush=True)
        return None
    
    return result.decode('utf-8').rstrip()

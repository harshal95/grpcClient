import subprocess
import sys
import os
from subprocess import Popen
def buildArgs(n, rank, u, port):
    res = "-Dexec.args=" + "\"" + n + " " + str(rank) + " " + u + " " + port + "\""
    print(res)
    return res

if __name__ == "__main__":
    mvn_build_list = ["mvn", "-f", "pom.xml", "clean", "install", "-U"]
    mvn_install_list = ["mvn", "exec:java"]
    working_dir = "/Users/sangeethasampathkumar/Desktop/ds_p1/grpcDemo"
    subprocess.check_call(mvn_build_list, cwd = working_dir)
#    subprocess.check_call(mvn_install_list, cwd = working_dir)
    
    
    n = sys.argv[1] # Number of processes
    update_node = sys.argv[2] # Update node of the process
    base_port = sys.argv[3] # Base port of the process-pool
    command_list = []
    #subprocess.check_call(mvn_build_list, cwd = working_dir)
    for i in range(int(n)):
        rank = i
        argString = buildArgs(n, rank, update_node, base_port)
        #mvn_install_list.append(argString)
        shell_command = (" ".join(mvn_install_list)) + " " + argString
        #subprocess.check_call(mvn_build_list, cwd = working_dir)
        #subprocess.check_call(mvn_install_list, cwd = working_dir)
        command_list.append(shell_command)
        base_port = str(int(base_port) + 1)
    
    print(command_list)
    processes = [Popen(cmd, cwd = working_dir, shell=True) for cmd in command_list]
    print(processes)

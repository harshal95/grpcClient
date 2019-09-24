import subprocess
import sys
import os

if __name__ == "__main__":
    cmd_template = ["lsof", "-ti"]
    killcmd_template = ["kill", "-9"]   
    n = sys.argv[1] # Number of processes
    base_port = sys.argv[2] # Base port
    for i in range(int(n)):
        port = i + int(base_port)
        cmd_list = cmd_template[:]
        cmd_list.append("tcp:" + str(port))
        print(cmd_list)
        try:
            pid_string = subprocess.check_output(cmd_list)
            pid_list = pid_string.decode('utf-8').split('\n')[:-1]
            print(pid_list)
            for p in pid_list:
                killcmd_list = killcmd_template[:]
                killcmd_list.append(str(p))
                try:
                    subprocess.check_output(killcmd_list)
                except subprocess.CalledProcessError as kill_exec:
                    print("call to kill failed")
        except subprocess.CalledProcessError as pid_exec:
            print("call to lsof failed")
   

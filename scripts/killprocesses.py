import subprocess
import sys
import os

if __name__ == "__main__":
    cmd = ["lsof", "-ti"]
    killcmd = ["kill", "-9"]   
    n = sys.argv[1] # Number of processes
    base_port = sys.argv[2] # Base port
    for i in range(int(n)):
        port = i + base_port
        cmd.append("TCP:" + str(port))
        portnum = subprocess.check_output(cmd)
        print(type(portnum))
        pn = portnum.decode('utf-8').rstrip('\n')
        killcmd.append(str(pn))
        subprocess.check_output(killcmd)
        cmd = cmd [: -1]
        killcmd = killcmd[: -1]
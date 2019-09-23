import subprocess
import sys
import os

if __name__ == "__main__":
    cmd = ["lsof", "-ti", "TCP:"]
	killcmd = ["kill", "-9"]   
    n = sys.argv[1] # Number of processes
    
    for i in range(int(n)):
    	port = i + 9090
    	cmd = cmd + port
        portnum = subprocess.check_call(cmd)
        killcmd = killcmd + " " + portnum
        subprocess.check_call(cmd)



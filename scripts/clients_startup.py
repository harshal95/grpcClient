import subprocess
import sys
import os
from subprocess import Popen



if __name__ == "__main__":
    base_command = "test-suite"
    working_dir = "/Users/sangeethasampathkumar/Desktop/ds_p1/grpcClient/client/test-suite/"
    input_file_fp = open("input_list.txt", "r") 
    input_file_list = input_file_fp.readlines()
    output_file_fp = open("output_list.txt", "r") 
    output_file_list = output_file_fp.readlines()
    command_list = [working_dir + base_command   + " " + working_dir + input_file_list[i].rstrip() + " " + working_dir + output_file_list[i].rstrip() for i in range(len(input_file_list))]
    print(command_list)
    processes = [Popen(command, cwd = working_dir, shell=True) for command in command_list]
    

import subprocess
import sys
import os
import random
if __name__ == "__main__":
    
	if(len(sys.argv) != 4):
		print("Run with params: n output_file hot/uniform(h/u):")
		exit(0)

	n = int(sys.argv[1])
	output_file = sys.argv[2]
	choice = sys.argv[3]

	key_list_fp = open("key_list.txt", "r")
	value_list_fp = open("value_list.txt", "r")

	output_file_fp = open(sys.argv[2], "w")

	key_list = [key.rstrip() for key in key_list_fp.readlines()]
	key_len = len(key_list)
	hot_key_len = int(0.1 * key_len)
	non_hot_key_len = key_len - hot_key_len

	prob_list = []
	
	for i in range(hot_key_len):
		prob_list.append(0.9/hot_key_len)

	for i in range(hot_key_len, key_len):
		prob_list.append(0.1/non_hot_key_len)


	value_list = [value.rstrip() for value in value_list_fp.readlines()]
	# ops = ["get", "put"]
	ops = ["put"]

	print("n is ", n)
	output_list = []
	if(choice == "h"):
		print("generating hot inputs")
	for i in range(n):
		if(choice == "h"):
			key = random.choices(key_list, k=1, weights=prob_list)[0]
		else:
			key = random.choices(key_list, k=1)[0]

		value = random.choices(value_list,k=1)[0]
		op = random.choices(ops, k=1)[0]
		output_str = ""
		if op == "get":
			output_str = op + "," + key
		elif op == "put":
			output_str = op + "," + key + "," + value

		output_list.append(output_str)

	# print(output_list)

	output_file_fp.writelines("%s\n" % operation for operation in output_list)
	output_file_fp.close()
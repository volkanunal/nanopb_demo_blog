CC = gcc
workspaceFolder = /home/volkan/Desktop/makefile
CFLAGS = -Wall -Werror -g -O0

# C source code files that are required
CSRC  = main.c                   # The main program
CSRC += led.pb.c                # The compiled protocol definition
CSRC += $(workspaceFolder)/nanopb/pb_encode.c  # The nanopb encoder
CSRC += $(workspaceFolder)/nanopb/pb_decode.c  # The nanopb decoder
CSRC += $(workspaceFolder)/nanopb/pb_common.c  # The nanopb common parts

main: main
	$(CC) $(CFLAGS) -omain $(CSRC)

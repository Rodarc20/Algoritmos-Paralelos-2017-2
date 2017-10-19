TRANSFER=scp
REXEC=ssh
SSHFLAGS=-C # Compress data
WORKDIR_SERVER=CUDAProjects/SumaVectores
REMOTE=rgutierrez@manati:~/$(WORKDIR_SERVER)
CC=/usr/local/cuda/bin/nvcc
FILES=sumavector.ct
SRC=sumavector.cu
EXEC_NAME=sumavector
NODES=2
dollar := $$

define script_content = 
#!/bin/bash\n#PBS -N test_$(EXEC_NAME)\n#PBS -l nodes=$(NODES)\ncd /home/rgutierrez/$(WORKDIR_SERVER)\n./a.out
endef


%.ct : %.cu
	$(TRANSFER) $(SSHFLAGS) $< $(REMOTE)
	touch $@


all-done: $(FILES)
	$(REXEC) $(SSHFLAGS) rgutierrez@manati "cd $(WORKDIR_SERVER) && pwd && $(CC) $(SRC) && echo -e '$(script_content)' > script.sh \
		&& chmod +x script.sh"
	touch all-done

clean:
	rm -f *.ct all-done


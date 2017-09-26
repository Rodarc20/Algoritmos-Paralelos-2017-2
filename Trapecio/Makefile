TRANSFER=scp
REXEC=ssh
SSHFLAGS=-C # Compress data
WORKDIR_SERVER=Trapecio
REMOTE=rgutierrez@manati:~/$(WORKDIR_SERVER)
CC=/opt/shared/openmpi-2.0.1/bin/mpicc
MPI_RUN=/opt/shared/openmpi-2.0.1/bin/mpirun
FILES=trapecio.ct
SRC=trapecio.c
EXEC_NAME=trapecio
NODES=2
dollar := $$

define script_content = 
#!/bin/bash\n#PBS -N test_$(EXEC_NAME)\n#PBS -l nodes=$(NODES)\ncd /home/rgutierrez/$(WORKDIR_SERVER)\n$(MPI_RUN) -n 64 ./a.out
endef


%.ct : %.c
	$(TRANSFER) $(SSHFLAGS) $< $(REMOTE)
	touch $@


all-done: $(FILES)
	$(REXEC) $(SSHFLAGS) rgutierrez@manati "cd $(WORKDIR_SERVER) && pwd && $(CC) $(SRC) && echo -e '$(script_content)' > script.sh \
		&& chmod +x script.sh"
	touch all-done

clean:
	rm -f *.ct all-done

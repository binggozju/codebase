SRCDIRS=zk_client
#SRCDIRS=zk_client more_dir

all:
	$(foreach N,$(SRCDIRS),make -C $(N);)
clean:
	$(foreach N,$(SRCDIRS),make -C $(N) clean;)

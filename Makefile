.SILENT:
.PHONY: FORCE

%.c: FORCE
	gcc $@ my_alloc.c -o $*
	./$* $(filter-out $@,$(MAKECMDGOALS))
	rm -f $*

FORCE:

%:
	@:

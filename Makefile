.SILENT:
.PHONY: FORCE

%.c: FORCE
	gcc $@ hall.c -o $*
	./$* $(filter-out $@,$(MAKECMDGOALS))
	rm -f $*

FORCE:

%:
	@:

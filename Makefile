.SILENT:
.PHONY: FORCE

%.c: FORCE
	gcc $@ -o $*
	./$* $(filter-out $@,$(MAKECMDGOALS))
	rm -f $*

FORCE:

%:
	@:

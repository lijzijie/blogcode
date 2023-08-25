cmd_/home/ziggy/a/Module.symvers := sed 's/\.ko$$/\.o/' /home/ziggy/a/modules.order | scripts/mod/modpost -m -a -E -o /home/ziggy/a/Module.symvers -e    -w -T -

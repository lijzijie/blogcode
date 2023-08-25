cmd_/home/ziggy/a/modules.order := {   echo /home/ziggy/a/hello.ko; :; } | awk '!x[$$0]++' - > /home/ziggy/a/modules.order

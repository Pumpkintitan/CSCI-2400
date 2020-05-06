# Directions

Full directions are in the [lab writeup file, shlab.pdf](shlab.pdf)

# Using GDB to debug your shell lab with VScode

If you plan on using VScode to debug your shell lab, we need to do a little configuration. Normally, GDB "catches" the same signals your shell is supposed to catch. This stops execution and returns control to GDB when those signals occur. This means you can't just set a breakpoint in your signal handlers and expect to have the debugger notice that. 

To get around this, we will use a [`.gdbinit`](.gdbinit) file which is contained in this Git repo. By default, `gdb` will not read a local `.gdbinit` file because of security concerns. We can override that by adding an option to the `.gdbinit` file in your home directory to enable loading any gdbinit file.

To do this, cut and paste the following line into a Terminal window

```
echo "set auto-load safe-path /" >> ~/.gdbinit
```

Following this, the local `.gdbinit` shoudld be loaded. If you want to change the local `.gdbinit` you can learn more about the signal configurations [at this GDB manual](https://sourceware.org/gdb/current/onlinedocs/gdb/Signals.html).
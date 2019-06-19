# ft_irc

Implementation of a client / server chat program.
You can connect multiple client to the server and create room or send private message to specific client.

Available commands are : \
/nick <name>         // change nickname \
/who                 // list users in the current channel \
/list                // list channels \
/msg <name>          // send private message \
/join <name>         // join the channel or create it if it doesn't exist \
/leave <name>        // leave the channel \
/exit                // close client \
/quit                // leave current server \
/connect <host port> // connect to a new server

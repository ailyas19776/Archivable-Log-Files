# Archivable-Log-Files

Take a look at the input Log Files.

To begin start by typing `source run.sh`

To run the program, start by inputting the log data (the user can also create their own log data, following the specified format below) and then inputting a commands text file (the user can also create their own commands, following the specified format below)

SAMPLE RUN (GIVEN TO YOU):./logfile master-file.txt < run-all-cmds.txt

CUSTON RUN :./logfile specified_log_file.txt < specified_cmds.txt 






# Specified Log Format
log_timestamp|category|description


*Make sure to use 4 colons in the timestamp*


ex: 


cat custom_log_file.txt


64:96:09:44:53|retruded|Unchurch halls chlorophenol consequent revenge calxes preconceiving Emanating guiltlessness donates 

68:33:74:21:60|hemikaryon|extradited Indorsing Serviette retrains piteous cercus Croplands penumbra haycock gluttons donates 





# Specified Command Keys

#### q command
% q

Terminates program

#### t command
% t \<timestamp1\>|\<timestamp2\>

 Grabs data between the specified timestamps


#### m command
% m \<timestamp\>

 Grabs data that matches specified timestamp
 
  
#### c command
% c \<category\>

Grabs data  that matches specified category
 
   
#### k command
% k \<string\>

Grabs data keyword search with  specified string
 
  
#### g command
% g

Prints most recent search from commnds including t,m,c,k
  
  
--------------------------------------
 DEQUE DATA STRUCTURE AS EXCERPT LIST
 ------------------------------------

 
#### a command
% a \<integer\>

Append log entry from integer position in master-log file into the excerpt list
 
  
#### r command
% r

Most recent search from command t,m,c,k will be appended into the excerpt list
 
  
#### d command
% d \<integer\>

 Delete log entry from integer position in the excerpt list
 
  
#### b command
% b \<integer\>

Move log entry at integer position in the excerpt list to the beginning
  
  
#### e command
% e \<integer\>

Move log entry at integer position in the excerpt list to the end
 
  
#### s command
% s

 Sort excerpt list by timestamps, with ties broken by category, and futher ties broken by the entryID
  
  
#### l command
% l

 Clear entire excerpt list
 
 
#### p command
% p

Prints entire excerpt list
 


# Specified Command Format
ex:


cat custom_commands.txt
 
 
c pinnacling

a 19187

a 39138

c balantidiosis

c forwardness

t 00:00:00:00:00|98:69:66:02:24

c interferometries

t 00:00:00:00:00|42:54:63:66:85

l

k formalin continuando

s

t 00:00:00:00:00|43:29:99:01:18

c interferometries

s

e 141

d 63  

k not chemoprophylaxis 

k astronomic

q
 
   

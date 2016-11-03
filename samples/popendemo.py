from subprocess import call
from subprocess import Popen, PIPE


# Run the ls command
process = Popen(["/usr/bin/ls", "-l"], stdout=PIPE)

# Grab the stdout and the stderr streams
(output, err) = process.communicate()

print(output)

# Wait for the process to finish and get the exit code
exit_code = process.wait()

# If the process exited with a code of 0, then it ended normally.
# Otherwise, it terminated abnormally
if exit_code == 0:
	retVal = output	


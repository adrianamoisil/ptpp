import sys

filename = sys.argv[1]
average = 0
count = 0

file_stream = open(filename, 'r')
lines = file_stream.readlines()
for line in lines:
  number = float(line)
  count += 1
  average += number

average /= count
print(count)
print(average)
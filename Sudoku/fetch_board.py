import urllib.request, sys

def main():
	ip = sys.argv[1]
	diff = sys.argv[2]
	with urllib.request.urlopen(ip + 
'?difficulty=' + 
diff) as req:
		response = req.read()
		with open('board.txt', 'w') as fout:
			fout.write(str(response)[2:-1])

if __name__ == '__main__':
	main()

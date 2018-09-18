import os


root_dir = os.getcwd()


target_exts = ['.cpp', '.h', '.txt', '.cs', '.py']
print('walk ... ' + root_dir)
for (root, dirs, files) in os.walk(root_dir):
	for filename in files:
		ext = os.path.splitext(filename)[1]
		if ext not in target_exts:
			continue
		filepath_src = os.path.join(root, filename)
		filepath_tmp = os.path.join(root, filename) + '.tmp'
		print("process = " + filepath_src)
		with open(filepath_src, 'rb') as f_in:
			with open(filepath_tmp, 'wb') as f_tmp:
				data = f_in.read()
				if data[0:3] == b'\xef\xbb\xbf':
					data = data[3:]
				data = data.replace(b'\r\n', b'\n')
				data = data.replace(b'\r', b'\n')
				if ext != '.txt':
					data = data.replace(b'	', b'\t')
				f_tmp.write(data)
		os.remove(filepath_src)
		os.rename(filepath_tmp, filepath_src)
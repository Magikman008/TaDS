from random import randint, shuffle

for r in [10, 100, 200, 300]:
	size = [r, r]

	matrix = [0] * (size[0] * size[1])

	persent = 30 #####################################

	for i in range(persent * size[0] * size[1]// 100):
		matrix[i] = randint(1, 100)
	shuffle(matrix)

	filename = str(size[0]) + '_' + str(size[1])+'_'+str(persent) + '.txt'
	f = open(filename, "w")
	f.write(str(size[0]) + '\n' + str(size[1]) + '\n')
	for i in range(size[0]):
		f.write(str(size[1] - matrix[i * size[1]: (i + 1) * size[1]].count(0))+'\n')

		for j in range(size[1]):
			if (matrix[i * size[1] + j] != 0):
				f.write(str(matrix[i * size[1] + j]) + ' ' + str(j) + '\n')

	f.write(str(size[0]) + '\n')
	vector = [0] * size[1]
	for i in range(persent * size[0]// 100):
		vector[i] = randint(1, 100)
	shuffle(vector)

	f.write(str(size[1] - vector.count(0)) + '\n')
	for i in range(size[1]):
		if (vector[i] != 0):
			f.write(str(vector[i]) + ' ' + str(i) + '\n')

	f.close()

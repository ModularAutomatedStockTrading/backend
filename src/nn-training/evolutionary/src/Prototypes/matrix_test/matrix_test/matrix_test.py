import random

def createRandomInstance(layers, nodesInLayers):
    NN =[]
    for i in range(0, (layers-1)):
        NN.append([])
        for j in range(0, nodesInLayers[i]):
            NN[i].append([])
            for k in range(0, nodesInLayers[i+1]):
                NN[i][j].append(random.randrange(1, 19)/10)
    return NN


NN =[[[1.1, 1.2], [1.3, 0.2], [1.2, 1.2], [1.3, 3.4]], [[0.9], [1.0]]]
#NN = createRandomInstance(3, [4, 2, 2])

for i in range(0, len(NN)):
    for j in range(0, len(NN[i])):
        print(NN[i][j])


def mult(a, b):
    c = []
    for i in range(0,len(a)):
        c.append([])
        for j in range(0,len(b[0])):
            c[i].append(0)
            for k in range(0,len(b)):
                c[i][j] += a[i][k] * b[k][j]

    return c
'''
a = [[1, 2, 3, 4], [3, 2, 1, 4], [2, 3, 1, 4]]
b = [[1, 2], [2, 1], [3, 3], [4, 4]]
c = mult(a,b)

for i in range(0, len(c)):
    print(c[i])
'''
def activate(a):
    return a

i = [[1, 2, 3, 4]]
def predict(input):
    In = input
    
    for l in range(0, len(NN)):
        #get out via activate(in)
        Out = []
        for i in range(0, len(In)):
            Out.append([])
            for j in range(0, len(In[i])):
                Out[i].append(activate(In[i][j]))
    
        #get in, for next layer, by multiplying out, from current layer, and weights, from current layer to next layer.
        In = mult(Out, NN[l])

    #print final output array
    for i in range(0, len(In[0])):
        print("[")
        for j in range(0, len(input[0])):
            print(input[0][j])
        print("] -->", In[0][i])
    return In

prediction = predict(i)
print(prediction)

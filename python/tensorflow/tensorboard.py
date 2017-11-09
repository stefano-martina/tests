import tensorflow as tf

# Model parameters
W = tf.Variable([.3], dtype=tf.float32)
b = tf.Variable([-.3], dtype=tf.float32)
# Model input and output
x = tf.placeholder(tf.float32)
linear_model = W*x + b
y = tf.placeholder(tf.float32)

tf.summary.scalar('W', W[0])
tf.summary.scalar('b', b[0])

# loss
loss = tf.reduce_sum(tf.square(linear_model - y)) # sum of the squares
tf.summary.scalar('loss', loss)

merged = tf.summary.merge_all()
writer = tf.summary.FileWriter("./summary")

# optimizer
optimizer = tf.train.GradientDescentOptimizer(0.01)
train = optimizer.minimize(loss)

# training data
x_train = [1, 2, 3, 4]
y_train = [0, -1, -2, -3]
# training loop
init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init) # reset values to wrong
for i in range(1000):
    summary = sess.run(merged, {x: x_train, y: y_train})
    writer.add_summary(summary, i)
    if (i%100) == 0:
        curr_W, curr_b, curr_loss = sess.run([W, b, loss], {x: x_train, y: y_train})
        print("{}-> W:{}; b:{}; loss:{}".format(i, curr_W, curr_b, curr_loss))

    sess.run(train, {x: x_train, y: y_train})
    
curr_W, curr_b, curr_loss = sess.run([W, b, loss], {x: x_train, y: y_train})
print("{}-> W:{}; b:{}; loss:{}".format(i, curr_W, curr_b, curr_loss))


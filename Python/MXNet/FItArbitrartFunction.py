"""
author: X.F. Zhou
email: mrchip.zxf@outlook.com
date: 2020.07
"""

# %% Import packages
from mxnet.gluon import loss, nn, data
from mxnet import autograd, nd, gluon, init
import mxnet as mx

import numpy as np
import matplotlib.pyplot as plt

device_ctx = mx.cpu()


def train_model(model, train_xs, train_ys):
    with device_ctx:
        # Convert to ndarray
        train_xs, train_ys = nd.array(train_xs), nd.array(train_ys)

        # Prepare the train dataset and model
        batch_size = 100
        train_dataset = data.ArrayDataset(train_xs, train_ys)
        train_data_iter = data.DataLoader(train_dataset,
                                          batch_size=batch_size,
                                          shuffle=True)

        # model = nn.Sequential()
        # model.add(nn.Dense(1, activation=None))
        # # model.add(nn.Dense(1))

        model.initialize(init.Normal(sigma=0.1))
        # model.initialize(init.Xavier())

        loss_f = loss.L2Loss()

        trainer = gluon.Trainer(model.collect_params(), 'sgd',
                                {'learning_rate': 0.05})

        # Train the model
        num_epochs = 25
        for epoch in range(1, num_epochs + 1):
            l = None
            for X, y in train_data_iter:
                with autograd.record():
                    # l = loss_f(model(X), y)
                    l = nd.power(model(X) - y, 2)
                l.backward()
                trainer.step(batch_size)

            # l = loss_f(model(train_xs), train_ys)
            l = nd.power(model(train_xs) - train_ys, 2) 
            mse = np.sum(
                np.power(
                    train_ys.asnumpy().reshape(-1, 1) -
                    model(train_xs).asnumpy().reshape(-1, 1),
                    2)) / len(train_xs)
            if epoch % 5 == 0:
                print('epoch %d, loss: %.4f, mse: %.4f' %
                      (epoch, l.mean().asnumpy(), mse))


# %% test for y = a*x+b
def get_data_f1(x, a, b, noise):
    """
    return function y = a * x + b + noise
    """
    y = a * x + b + noise * np.random.normal(size=x.shape)
    return y


# Generate the data
a = 2.375
b = 0.1126
noise = 1
train_xs = np.arange(-3, 3, 0.001).reshape(-1, 1)
train_ys = get_data_f1(train_xs, a, b, noise)

model = nn.Sequential()
model.add(nn.Dense(64, activation='relu'))
model.add(nn.Dense(16, activation='sigmoid'))
model.add(nn.Dense(1))
train_model(model, train_xs, train_ys)
# %%
ys_pre = model(nd.array(train_xs, device_ctx))
plt.figure()
plt.plot(train_xs, train_ys)
plt.plot(train_xs, ys_pre.asnumpy())
plt.legend(['train', 'predict'])
plt.show()

# # %%
# a_hat = model[0].weight.data().asnumpy()
# a_bias = model[0].bias.data().asnumpy()
# b_hat = model[1].weight.data().asnumpy()
# b_bias = model[1].bias.data().asnumpy()
# x_hat = np.array([-1])
# y_hat = np.dot((np.dot(x_hat.reshape(
#     (-1, 1)), a_hat.T) + a_bias), b_hat.T) + b_bias
# print(y_hat, a * x_hat + b)
# # %%


# %% for y =  A*exp(-(x-t/c)^2)
def get_data_f2(x, a, b, c, d, noise):
    """
    return function y = a*exp(-(x-b/c)^2) + d + noise
    """
    y = a * np.exp(-(
        (x - b) / c)**2) + d + noise * np.random.rand(x.shape[0], x.shape[1])
    return y


# %% Generate the data
a = 2.375
b = 0.1126
c = 1.2
d = 0.4
noise = 1
train_xs = np.arange(-10, 10, 0.001).reshape(-1, 1)
train_ys = get_data_f2(train_xs, a, b, c, d, noise)

model = nn.Sequential()
model.add(nn.Dense(64, activation='relu'))
model.add(nn.Dense(64, activation='relu'))
model.add(nn.Dense(64, activation='sigmoid'))
model.add(nn.Dense(32, activation='tanh'))
model.add(nn.Dense(1))
train_model(model, train_xs, train_ys)

ys_pre = model(nd.array(train_xs, device_ctx))
plt.figure()
plt.plot(train_xs, train_ys)
plt.plot(train_xs, ys_pre.asnumpy())
plt.legend(['train', 'predict'])
plt.show()

# %% for y =  A*exp(-(x-t/c)^2) with drop our
# Analyze the effect of activation function
# Generate the data
a = 2.375
b = 0.1126
c = 1.2
d = 0.4
noise = 1
train_xs = np.arange(-10, 10, 0.001).reshape(-1, 1)
train_ys = get_data_f2(train_xs, a, b, c, d, noise)

model = nn.Sequential()
model.add(nn.Dense(64, activation='relu'))
# model.add(nn.Dropout(0.3))
# model.add(nn.Dense(64, activation='sigmoid'))
# model.add(nn.Dense(32, activation='tanh'))
model.add(nn.Dense(64, activation='relu'))
model.add(nn.Dense(1))
train_model(model, train_xs, train_ys)

ys_pre = model(nd.array(train_xs, device_ctx))
plt.figure()
plt.plot(train_xs, train_ys)
plt.plot(train_xs, ys_pre.asnumpy())
plt.legend(['train', 'predict'])
plt.show()

# %% for y =  A*exp(-(x-t/c)^2) with drop our
# Analyze the effect of activation function
# Generate the data

# %% for y =  A*exp(-(x-t/c)^2)
def get_data_f3(x, a, b, c, d, noise):
    """
    return function y = a*exp(-(x-b/c)^2) + d + noise
    """
    y = x + a*np.exp(-(x-b/c)**2) + d + noise * np.random.rand(x.shape[0], x.shape[1])
    return y

a = 2.375
b = 0.1126
c = 1.2
d = 0.4
noise = 0.1
train_xs = np.arange(-10, 10, 0.01).reshape(-1, 1)
train_ys = get_data_f3(train_xs, a, b, c, d, noise)
# train_ys = get_data_f1(train_xs, a, b, noise)

model = nn.Sequential()
model.add(nn.Dense(64, activation='sigmoid'))
model.add(nn.Dense(64, activation='sigmoid'))
# model.add(nn.Dense(64, activation='sigmoid'))
# model.add(nn.Dense(64, activation='relu'))
model.add(nn.Dense(1))
train_model(model, train_xs, train_ys)

ys_pre = model(nd.array(train_xs, device_ctx))
plt.figure()
plt.plot(train_xs, train_ys)
plt.plot(train_xs, ys_pre.asnumpy())
plt.legend(['train', 'predict'])
plt.show()
# %%

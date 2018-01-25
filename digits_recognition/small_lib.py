#!/usr/bin/env python3

import random

 # Нашлась готовая библиотека для этих данных
from mnist import MNIST


# Создается некоторый объект, который управляет этими данными
# Все, что нужно передать в конструктор, - путь до директории с 4 файлами:
#               t10k-images-idx3-ubyte  
#               t10k-labels-idx1-ubyte  
#               train-images-idx3-ubyte  
#               train-labels-idx1-ubyte
mndata = MNIST('datasets/mnist_digits') 

# Создаем список векторных представлений изображений и список меток из данных для обучения
training_images, training_labels = mndata.load_training() 

# То же самое, но для тестирования
testing_images, testing_labels = mndata.load_testing()

# Есть удобный способ отображения картинки прямо в консольке! Просто мечта разработчика с линуксом!
print( mndata.display(training_images[0]) )

# Вот сама метка для самой первой картинки
print( "label for first image : {}".format(training_labels[0]))

# А вот то же изображение, но в векторном формате 
# (не в смысле векторная графика, а в смысле в виде массива)
# Это можно сразу подавать на вход нейросети
print( training_images[0] )

# Длины всех векторов одинаковы и равны:
print( "Length of image vector = {}".format(len(training_images[0])))

# Этих функций, думаю, достаточно
# Если что-то неясно или не работает - гугли или пиши!
# Удачи!!!




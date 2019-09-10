# -*- coding: utf-8 -*-
"""
Created on Wed Aug 28 19:57:48 2019

@author: lucas
"""

import os
import shutil

arq_dat = os.listdir(r'C:\Users\lucas\Desktop\PA\tspdl-test-data-equal-demand')

for arquivo in arq_dat:
    distance = False #False quando estiver fora da matriz de distâncias
    draft = False
    n = 0 #quantidade de nós no grafo
    i = 0 #vai percorrer as linhas da matriz para controlar quando sair do if
    with open(arquivo) as f:
        for line in f:
            if line.startswith('N:'):
                aux = line.split() #separa N: dos números de nós
                n = int(aux[1])
                matriz = [[0 for col in range(n)] for row in range(n)] #inicializa a matriz de distâncias
                continue
            elif line.startswith('Distance'):
                distance = True
                continue
            elif line.startswith('Draft'):
                draft = True
                continue
            elif distance == True:
                aux = line.split()
                for k in range(n):
                    matriz[i][k] = int(aux[k])
                i = i + 1 # se for do mesmo tamanho de n, significa que já percorreu a matriz inteira
                if i == n:
                    distance = False
            elif draft == True:
                aux = line.split()
                lista_draft = []
                for k in range(n):
                    lista_draft.append(int(aux[k]))
                draft = False
    
    aux = arquivo.split('.')
    novo = aux[0] + '_py.' + aux[1]
    
    file = open(novo, 'w')
    
    file.write("%d\n" % n)
    
    for i in range(n):
        for j in range(n):
            file.write("%d\n" % matriz[i][j])
    
    for i in range(n):
        file.write("%d\n" % lista_draft[i])
    
    file.close()
    shutil.move(novo, r'C:\Users\lucas\Desktop\PA\processados')
    
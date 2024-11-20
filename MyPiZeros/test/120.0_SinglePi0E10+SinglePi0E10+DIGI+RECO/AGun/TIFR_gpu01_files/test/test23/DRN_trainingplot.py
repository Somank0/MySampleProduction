import numpy as np
import pickle
import matplotlib.pyplot as plt
import matplotlib

#matplotlib.use('pgf')
#matplotlib.rcParams['pgf.texsystem'] = 'pdflatex'

pred = np.array(np.load("pred.pickle",allow_pickle=True)).flatten()
true = np.array(np.load("trueE_target.pickle",allow_pickle=True)).flatten()
file=open("all_trainidx.pickle",'rb')
tidx=np.array(pickle.load(file))
file=open("all_valididx.pickle",'rb')
vidx=np.array(pickle.load(file))

predv=pred[vidx]
predt=pred[tidx]
truev=true[vidx]
truet=true[tidx]

plt.hist2d(np.array(truet),np.array(predt),bins=50,range=[[0,3],[0,3]],cmin=5) 
plt.colorbar()
plt.title("Training sample ( " + str(len(predt)) + " events )",fontsize=16)
plt.ylabel(f'Predicted $M_a$',fontsize=14,loc='top')
plt.xlabel(f'True $M_a$',fontsize=14,loc='right')
plt.tick_params(axis='x', which='major', labelsize=12, length=6)  # Increase x-axis major tick size to 12
plt.tick_params(axis='y', which='major', labelsize=12, length=6)  # Increase y-axis major tick size to 12
plt.savefig("predvstrue_train.png",bbox_inches='tight')
plt.savefig("predvstrue_train.pdf",bbox_inches='tight')
plt.clf()

plt.hist2d(np.array(truev),np.array(predv),bins=50,range=[[0,3],[0,3]],cmin=5) 
plt.colorbar()
plt.title("Validation sample ( " + str(len(predv)) + " events )",fontsize=16)
plt.ylabel(f'Predicted $M_a$',fontsize=14,loc='top')
plt.xlabel(f'True $M_a$',fontsize=14,loc='right')
plt.tick_params(axis='x', which='major', labelsize=12, length=6)  # Increase x-axis major tick size to 12
plt.tick_params(axis='y', which='major', labelsize=12, length=6)  # Increase y-axis major tick size to 12
plt.savefig("predvstrue_valid.png",bbox_inches='tight')
plt.savefig("predvstrue_valid.pdf",bbox_inches='tight')
plt.clf()

s = np.load("summaries.npz")
tloss=s['train_loss']
vloss=s['valid_loss']
epoch=s['epoch']
plt.plot(epoch,tloss,'-',label="Training Loss")
plt.plot(epoch,vloss,'-',label="Validation Loss")
x,y = np.argmin(vloss),np.min(vloss)
plt.axhline(y, color='r', linestyle='--',label='Best model\nMin Loss: '+str(y)+', Epoch: '+str(x))
plt.axvline(x, color='r', linestyle='--')
plt.xlabel("Epoch",fontsize=14,loc='right')
plt.ylabel("Loss",fontsize=14,loc='top')
plt.tick_params(axis='x', which='major', labelsize=12, length=6)  # Increase x-axis major tick size to 12
plt.tick_params(axis='y', which='major', labelsize=12, length=6)  # Increase y-axis major tick size to 12
plt.legend(fontsize=12)
plt.savefig("lossvsepoch.png",bbox_inches='tight')
plt.savefig("lossvsepoch.pdf",bbox_inches='tight')

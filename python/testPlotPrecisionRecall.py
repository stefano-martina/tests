import matplotlib
matplotlib.use('pdf')
import matplotlib.pyplot as plt
import numpy as np
import sklearn as sl
import sklearn.datasets
import sklearn.svm
import sklearn.cross_validation


iris = sl.datasets.load_iris()
X = iris.data
y = iris.target

y = sl.preprocessing.label_binarize(y, classes=np.unique(y))

random_state = np.random.RandomState(0)

X_train, X_test, y_train, y_test = sl.cross_validation.train_test_split(X, y, test_size=.1, random_state=random_state)

classifier = sklearn.multiclass.OneVsRestClassifier(sklearn.svm.SVC(kernel='linear', probability=True, random_state=random_state))

y_score = classifier.fit(X_train, y_train).decision_function(X_test)

precision, recall, threshold = sklearn.metrics.precision_recall_curve(y_test.ravel(),y_score.ravel())
average_precision = sklearn.metrics.average_precision_score(y_test, y_score, average="micro")

plt.clf()
ax = plt.figure().gca()
ax.set_xticks(np.arange(0,1,0.05))
ax.set_yticks(np.arange(0,1.,0.05))
plt.xticks(rotation='vertical')
plt.plot([0.,1.],[0.,1.], color='blue')
plt.plot(recall, precision, color='gold', lw=2, label='micro-average Precision-recall curve (area = {0:0.2f})'''.format(average_precision))

plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.05])
plt.xlabel('Recall')
plt.ylabel('Precision')
#plt.title('Precision-Recall curve')
plt.legend(loc="lower right")
plt.grid()
plt.savefig("test.pdf")


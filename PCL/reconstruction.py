import numpy as np
import cv2
import sys

focal_length = 26  # en mm
sensor_width = 6.2  # en mm (pour Samsung S21)

# Dimensions de l'image
img_width = 4032
img_height = 1816

# Calcul des paramètres de la matrice de projection
fx = fy = focal_length * img_width / sensor_width
cx = img_width / 2
cy = img_height / 2

#fx = 3410.99
#fy = 3412.37 
# Construction de la matrice de projection
K = np.array([[fx, 0, cx],
              [0, fy, cy],
              [0, 0, 1]])

print("Matrice de projection :")
print(K)
print(sys.argv[1])
print(sys.argv[2])
print(sys.argv[3])

# Lecture des images
img1 = cv2.imread(sys.argv[1])
img2 = cv2.imread(sys.argv[2])
# Détection des points d'intérêt et calcul des descripteurs
detector = cv2.SIFT_create()


kp1, des1 = detector.detectAndCompute(img1, None)
kp2, des2 = detector.detectAndCompute(img2, None)

# Correspondance des points d'intérêt
FLANN_INDEX_KDTREE = 1
index_params = dict(algorithm=FLANN_INDEX_KDTREE, trees=5)
search_params = dict(checks=50)
bf = cv2.FlannBasedMatcher(index_params, search_params)
matches = bf.knnMatch(des1, des2, k=2)

# Tri des correspondances en fonction de leur distance
# matches = sorted(matches, key=lambda x: x.distance)

# print(kp1)

# Sélection des correspondances les plus fiables
# good_matches = matches[:50]
good_matches = []
for m, n in matches:
    if m.distance < 0.68 * n.distance:
        pt1 = kp1[m.queryIdx].pt
        pt2 = kp2[m.trainIdx].pt
        angle1 = kp1[m.queryIdx].angle
        angle2 = kp2[m.trainIdx].angle
        if abs(angle1 - angle2) < 10: # le seuil de l'angle est fixé à 10 degrés
            good_matches.append(m)


# Dessiner les correspondances
img_matches = cv2.drawMatches(img1, kp1, img2, kp2, good_matches, None, flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)
# points1_indices = np.array([match.queryIdx for match in matches])
# points2_indices = np.array([match.trainIdx for match in matches])

# # Extraire les coordonnées des points correspondants dans les deux images
# pts1 = np.array([kp1[idx].pt for idx in points1_indices])
# pts2 = np.array([kp2[idx].pt for idx in points2_indices])


# Dessin des correspondances
# img3 = cv2.drawMatches(img1, kp1, img2, kp2, matches, None, flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)

# Affichage de l'image résultante
# cv2.imwrite("Matches.JPG", img_matches)
# Extraction des coordonnées des correspondances dans les deux images
pts1 = np.float32([kp1[m.queryIdx].pt for m in good_matches])
pts2 = np.float32([kp2[m.trainIdx].pt for m in good_matches])

pts1 = np.array(pts1)
pts2 = np.array(pts2)

R_t_0 = np.array([[1,0,0,0], [0,1,0,0], [0,0,1,0]])
R_t_1 = np.empty((3,4))

P1 = np.matmul(K, R_t_0)
P2 = np.empty((3,4))

F, mask = cv2.findFundamentalMat(pts1, pts2, cv2.RANSAC)

E = np.matmul(np.matmul(np.transpose(K), F), K)

_, R, t, mask = cv2.recoverPose(E, pts1, pts2, K)

R_t_1[:3,:3] = np.matmul(R, R_t_0[:3,:3])
R_t_1[:3, 3] = R_t_0[:3, 3] + np.matmul(R_t_0[:3,:3],t.ravel())

P2 = np.matmul(K, R_t_1)

# Calcul de la matrice d'homographie
# H, _ = cv2.findHomography(pts1, pts2, cv2.RANSAC)

pts1 = np.transpose(pts1)
pts2 = np.transpose(pts2)

# print(good_matches.shape)

# Définition de la rotation de 10 degrés autour de l'axe Y
# theta = 10 * np.pi / 180  # conversion des degrés en radians
# R = cv2.Rodrigues(np.array([0, theta, 0]))[0]
# # Définition du vecteur de translation
# d = 0.5
# t = np.array([[0], [0], [d]])

# extrinsic1 = np.array([[1, 0, 0, 0.5],
#                         [0, 1, 0, 0],
#                         [0, 0, 1, 0]])

# extrinsic2 = np.array([[0.9848077297210693, 0, 0.1736481785774231, 0.5],
#                         [ 0, 1, 0, 0],
#                         [-0.1736481785774231, 0, 0.9848077297210693, 0]])

# # print(extrinsic1)
# # Ajout d'une colonne de zéros à K
# # K_homog = np.hstack((K, np.zeros((3, 1))))

# # Création de la matrice de transformation homogène 4x4
# P1 = np.dot(K, extrinsic1)
# # mat = np.concatenate(R,t)
# P2 = np.dot(K, extrinsic2)

# Calcul des points 3D
# h, w, _ = img1.shape
# pts1 = np.array([[0, 0], [0, h], [w, h], [w, 0]], dtype=np.float32).reshape(-1, 1, 2)
# pts2 = cv2.perspectiveTransform(pts1, H)
# print(pts1)
points4D = cv2.triangulatePoints(P1, P2, pts1, pts2)

points3D = []
for i in range(points4D.shape[1]):
    point3D = points4D[:, i] / points4D[3, i]
    points3D.append(point3D[:-1])
# points4D /= points4D[3]
# print(points3D.shape)

# Affichage du résultat en 3D
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

# Supposons que la liste de points est appelée "points_list"
points_array = np.array(points3D)
print(points_array.shape)
# Ouvrir le fichier en mode écriture
file = open(sys.argv[3], "w")

# Écrire du texte dans le fichier
file.write("OFF\n")
file.write(str(points_array.shape[0])+" 0 0\n")
for pt in points_array:
    file.write(str(pt[0]) +" "+ str(pt[1]) +" "+str(pt[2])+"\n")

# Fermer le fichier
file.close()

# Créer une figure
# fig = plt.figure()
# ax = fig.add_subplot(111, projection='3d')

# # Tracer les points
# ax.scatter(points_array[:, 0], points_array[:, 1], points_array[:, 2])

# # Ajouter des étiquettes aux axes
# ax.set_xlabel('X')
# ax.set_ylabel('Y')
# ax.set_zlabel('Z')

# # Afficher le graphique
# plt.show()

# fig = plt.figure()
# ax = fig.add_subplot(111, projection='3d')
# for i in range(0,len(points_array), 3):
#     # if pts3d[i] != pts3d[i+1] != pts3d[i+2] != '':
#         ax.scatter(points_array[i], points_array[i+1] , points_array[i+2])
#         # ax.scatter(float(pts3d[3]), float(pts3d[4]) , float(pts3d[5]))
#         # ax.scatter(float(pts3d[6]), float(pts3d[7]) , float(pts3d[8]))
# plt.show()



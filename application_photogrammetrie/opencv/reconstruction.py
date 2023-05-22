import numpy as np
import cv2
import sys

focal_length = 26  # en mm
sensor_width = 6.2  # en mm (pour Samsung S21)
# sensor_width = 5.76 #en mm (Iphone XR)

# Dimensions de l'image
img_width = 4032
img_height = 1816

# Calcul des paramètres de la matrice intrinsèque
fx = fy = focal_length * img_width / sensor_width
cx = img_width / 2
cy = img_height / 2

# Distance focale pour la statue
#fx = 3410.99
#fy = 3412.37 

"""Construction de la matrice de intrinsèque"""
intrinsic = np.array([[fx, 0, cx],
              [0, fy, cy],
              [0, 0, 1]])


# print("Matrice de projection :")
# print(intrinsic)
# print(sys.argv[1])
# print(sys.argv[2])
# print(sys.argv[3])

"""Lecture des images"""
img1 = cv2.imread(sys.argv[1])
img2 = cv2.imread(sys.argv[2])


"""Détection des points d'intérêt et calcul des descripteurs"""
detector = cv2.SIFT_create()
kp1, des1 = detector.detectAndCompute(img1, None)
kp2, des2 = detector.detectAndCompute(img2, None)


"""Correspondance des points d'intérêt avec BruteForce et KNN"""
# FLANN = Fast Library for Approximate Nearest Neighbors
# k-NN = k - Nearest Neighbors (ici k = 2)
# index_params = généralement utilisé avec SIFT
# search_params = nombre de fois que l'arbre est traversé récursivement
FLANN_INDEX_KDTREE = 1
index_params = dict(algorithm=FLANN_INDEX_KDTREE, trees=5)
search_params = dict(checks=50)
bf = cv2.FlannBasedMatcher(index_params, search_params)
matches = bf.knnMatch(des1, des2, k=2)

"""Filtrage des correspondances"""
# Filtrage par la distance et l'angle
# l'angle correspond à l'orientation du point d'intérêt
good_matches = []
for m, n in matches:
    if m.distance < 0.68 * n.distance:
        pt1 = kp1[m.queryIdx].pt
        pt2 = kp2[m.trainIdx].pt
        angle1 = kp1[m.queryIdx].angle
        angle2 = kp2[m.trainIdx].angle
        if abs(angle1 - angle2) < 10: 
            good_matches.append(m)


"""Dessiner les correspondances"""
# drawMatches permet de dessiner les correspondances entre les deux images
img_matches = cv2.drawMatches(img1, kp1, img2, kp2, good_matches, None, flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)


"""Extraction des coordonnées des correspondances dans les deux images"""
pts1 = np.float32([kp1[m.queryIdx].pt for m in good_matches])
pts2 = np.float32([kp2[m.trainIdx].pt for m in good_matches])
pts1 = np.array(pts1)
pts2 = np.array(pts2)


"""Initialisation des matrices de rotations des deux images"""
extrinsic1 = np.array([[1,0,0,0], [0,1,0,0], [0,0,1,0]])
extrinsic2 = np.empty((3,4))


"""Initialisation des matrices de projections"""
# P1 est le produit de la matrice intrinsèque par la première matrice de rotation
P1 = np.matmul(intrinsic, extrinsic1)
P2 = np.empty((3,4))


"""Calcul de la deuxième matrice de projection"""
# F est calculée à partir des points d'intérêt
# E est calculée avec la formule : E = transpose(intrinsic) * F * intrinsic
# recoverPose permet de calculer la rotation entre les deux images à partir de E, intrinsic et les points d'intérêt des deux images
# calcul de la deuxième matrice de rotation en effectuant le produit entre la première matrice de rotation et la matrice de rotation (extraite avec recoverPose)
# mis à jour de la translation entre les deux images en utilisant la matrice de translation t (extraite avec recoverPose)
# P2 est le produit de la matrice intrinsèque par la deuxième matrice de rotation
F, mask = cv2.findFundamentalMat(pts1, pts2, cv2.RANSAC)
E = np.matmul(np.matmul(np.transpose(intrinsic), F), intrinsic)
_, R, t, mask = cv2.recoverPose(E, pts1, pts2, intrinsic)
extrinsic2[:3,:3] = np.matmul(R, extrinsic1[:3,:3])
extrinsic2[:3, 3] = extrinsic1[:3, 3] + np.matmul(extrinsic1[:3,:3],t.ravel())
P2 = np.matmul(intrinsic, extrinsic2)


"""Triangulation des points"""
# Transposition des points pour cv2.triangulatePoints()
# Triangulation des points en utilisant les deux matrices de projection calculées P1 et P2
# points4D = points 3D en coordonnées homogènes
# points3D = points 3D finaux (obtenus en divisant les trois premières coordonnées par la dernière)
pts1 = np.transpose(pts1)
pts2 = np.transpose(pts2)
points4D = cv2.triangulatePoints(P1, P2, pts1, pts2)
points3D = []
for i in range(points4D.shape[1]):
    point3D = points4D[:, i] / points4D[3, i]
    points3D.append(point3D[:-1])
points_array = np.array(points3D)



"""Création d'un fichier contenant l'ensemble des points 3D"""
# Ouvrir le fichier en mode écriture
# Écrire du texte dans le fichier
# Fermer le fichier
file = open(sys.argv[3], "w")
file.write("OFF\n")
file.write(str(points_array.shape[0])+" 0 0\n")
for pt in points_array:
    file.write(str(pt[0]) +" "+ str(pt[1]) +" "+str(pt[2])+"\n")
file.close()




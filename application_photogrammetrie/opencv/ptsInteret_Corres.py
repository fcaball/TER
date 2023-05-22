import cv2
import numpy as np
import sys

print(sys.argv[4])
# Charger les deux images
img1 = cv2.imread(sys.argv[1])
if(sys.argv[4]!="0"):
    img2 = cv2.imread(sys.argv[2])
gray= cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)

# Créer un objet SIFT pour extraire les descripteurs
sift = cv2.SIFT_create()

# Trouver les points d'intérêt et les descripteurs pour les deux images
kp1, des1 = sift.detectAndCompute(img1, None)
if(sys.argv[4]!=0):
    kp2, des2 = sift.detectAndCompute(img1, None)

for point in kp1:
    x, y = point.pt
    cv2.circle(img1, (int(x), int(y)), 5, (0, 0, 255), -1)

# imgKp = cv2.drawKeypoints(img2, kp2, None, flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
directory=sys.argv[3]
cv2.imwrite(directory+"KeyPoints.jpg", img1)

if(sys.argv[4]!="0"):
    # Créer un objet BFMatcher pour faire la correspondance entre les descripteurs
    FLANN_INDEX_KDTREE = 1
    index_params = dict(algorithm=FLANN_INDEX_KDTREE, trees=5)
    search_params = dict(checks=50)
    bf = cv2.FlannBasedMatcher(index_params, search_params)
    matches = bf.knnMatch(des1, des2, k=2)

    good_matches = []
    for m, n in matches:
        if m.distance < 0.68 * n.distance:
            pt1 = kp1[m.queryIdx].pt
            pt2 = kp2[m.trainIdx].pt
            angle1 = kp1[m.queryIdx].angle
            angle2 = kp2[m.trainIdx].angle
            if abs(angle1 - angle2) < 10: # le seuil de l'angle est fixé à 10 degrés
                good_matches.append(m)

    print(len(good_matches))
    # img4 = cv2.drawMatches(img1, kp1, img2, kp2, good_matches, None, flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)

    img3 = cv2.drawMatches(img1, kp1, img2, kp2, good_matches, None, flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)

    cv2.imwrite(directory+"CorrespondanceFiltree.jpg", img3)
    # cv2.imwrite("CorrespondanceNONFiltree.jpg", img4)

# Face Detection – Proiect C++ cu OpenCV

Acest proiect implementează un sistem de detecție facială în timp real, folosind biblioteca OpenCV și clasificatorul Haar Cascade.

## Funcționalitate

- Detectarea fețelor în timp real din fluxul camerei web
- Suprapunere dreptunghiuri peste fețele detectate
- Poziționare în centrul imaginii (crosshair)
- Afișare număr de față detectate
- Buton de ieșire cu `ESC`

## Fișiere proiect

| Fișier                            | Descriere                                    |
|----------------------------------|----------------------------------------------|
| `test.cpp`                       | Codul sursă principal                        |
| `haarcascade_frontalface_default.xml` | Clasificator Haar pre-antrenat        |
| `FaceDetection.vcxproj`          | Fișier de proiect Visual Studio             |
| `FaceDetection.vcxproj.filters`  | Structură directoare pentru surse VS       |
| `FaceDetection.vcxproj.user`     | Setări locale Visual Studio (user)          |

## Cerințe

- Visual Studio 2019+ (sau alt IDE compatibil C++)
- OpenCV instalat și setat corect în proiect
- WebCam activă pentru rulare live

## Compilare și rulare

1. Deschide `FaceDetection.vcxproj` în Visual Studio
2. Configurează calea către OpenCV în: C/C++ → General → Additional Include Directories
3. Adaugă și `.lib`-urile în: Linker → Input → Additional Dependencies
4. Rulează `test.cpp` din IDE
5. Apasă `ESC` pentru a închide aplicația

## Rezultat așteptat

- Ferestre video live cu fețele încadrate
- Afișare dinamică a numărului de fețe detectate

## Autor

Proiect C++ cu OpenCV pentru detecția fețelor din cameră – educațional, real-time.

ofxTextureExtension
===================

ofxCubeTexture and ofx1DTexture, extension of the ofTexture.

CubeTexture,1DTextureの取り急ぎ版。

Image Based Lighting とかで使ってますが、通常はskybox等が簡単に作れるぐらいしか用途は思い浮かびません。

ofTextureを拡張してるので bind,draw等のメソッドやofShaderへのuniform参照が利用できます。
openframeworksは現在のgithub（https://github.com/openframeworks/openFrameworks ）(9以降)でしか動かないと思います。

cubeMapの貼り付けはいくつか手法がありますのでexamlpeの参考画像を見て下さい。
また、ofTextureと同じですがHDRテクスチャを遣う場合はallocateでの指定が必須となります。




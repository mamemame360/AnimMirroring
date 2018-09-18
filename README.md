# UE4 AnimMirroring Plugin

アニメーションの「ミラーリング」を行うプラグインです。

ローカルスペースでミラーリングを行うノードと、コンポーネントスペースでミラーリングを行う２つのノードを用意しています。

![スクリーンショット](https://media.githubusercontent.com/media/mamemame360/AnimMirroring/master/images/screenshot.png "screenshot")

# インストール

1. {UnrealProjectPath}/Pluginsの下にリポジトリをコピー
2. {UnrealProjectPath}/{UnrealProjectName}.uprojectファイルを右クリックして[Generate VisualStudio Project files]を選択。
3. 生成されたslnを使ってビルド。

# 使い方(マネキンの場合)

1. アニメーションブループリントのAnimGraphを開いて、「ComponentSpaceMirroring」のノードを追加。
2. 追加したノードの「Details - Settings」で、「Mirroring Data」のアセットを新規作成。
3. 追加したアセットを開いて「Name Rule」を「Tail Match」、「Bone Name」を「_l」、「Pair Bone Name」を「_r」、「Mirror Axis」を「XAxis」に設定。
これで末尾が_lと_rで対応している名前同士のボーンを反転させます。
4. 「Default Mirror Axis」を「XAxis」に変更。これでペアリング以外のノードもX軸にミラーリングを行います。

これでアニメーションがミラーリングされるはずです。

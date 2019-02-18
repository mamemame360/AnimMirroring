# UE4 AnimMirroring Plugin

![スクリーンショット](https://media.githubusercontent.com/media/mamemame360/AnimMirroring/master/images/screenshot.png "screenshot")

## 概要 / Overview

(Japanese)

アニメーションの「ミラーリング」を行うプラグインです。

ローカルスペースでミラーリングを行うノードと、コンポーネントスペースでミラーリングを行う２つのノードを用意しています。


(English)

This plug-in is provide "animation mirroring".

We have two type animnode: local scape mirroring and component space mirroring.


## Install / インストール

(Japanese)

1. {UnrealProjectPath}/Pluginsの下にリポジトリをコピー
2. {UnrealProjectPath}/{UnrealProjectName}.uprojectファイルを右クリックして[Generate VisualStudio Project files]を選択。
3. 生成されたslnを使ってビルド。


(English)

1. Clone the repositry under "{UnrealProjectPath}/Plugins" directory.
2. Right click on the {UnrealProjectPath}/{UnrealProjectName}.uproject" file and select "Generate VisualStudio Project files".
3. Build with generated sln.

## How to use / 使い方 (In case of "Mannequin" / 「マネキン」の場合)

(Japanese)

1. アニメーションブループリントのAnimGraphを開いて、「ComponentSpaceMirroring」のノードを追加。
2. 追加したノードの「Details - Settings」で、「Mirroring Data」のアセットを新規作成。
3. 追加したアセットを開いて「Name Rule」を「Tail Match」、「Bone Name」を「_l」、「Pair Bone Name」を「_r」、「Mirror Axis」を「XAxis」に設定。
これで末尾が_lと_rで対応している名前同士のボーンを反転させます。
4. 「Default Mirror Axis」を「XAxis」に変更。これでペアリング以外のノードもX軸にミラーリングを行います。


(English)

1. Open AnimGraph of AnimBlueprint and add "ComponentSpaceMirroring" node.
2. Create an asset of "Mirroring Data" with "Details - Settings" of the added node.
3. Open the added asset and set "Name Rule" to "Tail Match", "Bone Name" to "_l", "Pair Bone Name" to "_r" and "Mirror Axis" to "XAxis".
This will invert the bones of the names whose names end with "_l" and "_r".
4. Change "Default Mirror Axis" to "XAxis". Now nodes other than pairing mirror on the X axis.

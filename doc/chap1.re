= 一日目
== はじめに

 * 目標: 「マインスイーパ」をAndroidアプリとして実装してみる
 * 前提: JavaとEclipseの扱いが少し分かること
 ** Javaで@<code>{if}, @<code>{for}といった概念が分かる。
 *** メソッド等についても書き方が分かる
 *** 名前空間、@<code>{import}についてひと通り理解している
 *** 継承の概念、インターフェース等を理解している
 *** @<code>{instanceof}やキャストについても理解できる
 ** EclipseとAndroid SDKのインストール、ADTの準備ができている
 *** EclipseでAndroidプロジェクトのインポートが出来る


=== 「マインスイーパ」とは

 * @<href>{http://goo.gl/yBHU77} (マインスイーパ - Wikipedia)
 * @<href>{http://minesweeperonline.com/#beginner}
 ** 画像を@<img>{minesweeper}, @<img>{minesweeper2}, @<img>{minesweeper3}, @<img>{minesweeper4}に示す。

//image[minesweeper][マインスイーパの開始画面]{
//}

//image[minesweeper2][マインスイーパのプレイ最中の画面]{
//}

//image[minesweeper3][マインスイーパのクリア画面]{
//}

//image[minesweeper4][マインスイーパのゲームオーバー画面。赤く塗られたマスをクリックしてしまった。]{
//}

このゲーム（の簡略化版）をAndroid上で動くアプリとして作ってみる。

=== マインスイーパの「仕様」

//quote{
仕様（しよう、英: Specification）とは、材料・製品・サービスが明確に満たさなければならない要求事項の集まりである。仕様を記述した文書を仕様書と呼ぶ。
(仕様 - Wikipedia)
//}

 * 今回の「仕様」は厳密である必要はない
 ** 他人に作ってもらうわけではないので、曖昧な部分があっても自分が処理できる
 * 概要から詳細へ
 ** どういうゲームであって欲しいか
 ** ゲームとして、どのような要素が必要か
 ** どのような画面にして、どこをクリックしたらどう動くのか
 * 簡単なゲームなら頭の中である程度まとめ時点で実装を始められる
 ** 今回、どういうゲームかは明らかなので、それを達成する要素から考えていく。
 ** 難しい場合は、「仕様書」のレベルで考える要素が多い。

=== どのような要素が必要か

 * ボタンが格子状（マス目状）に配置されている
 ** 一部は爆弾で、他は空
 * マスをクリックすると、爆弾かどうかが判明する
 ** 何もないところと爆弾のあるところ
 ** 何もないところでは「数字」が表示されることもある
 *** 数字は周囲8マスの爆弾の数を表している
 * 爆弾を避けて全て掘れたら「クリア」
 * 今回は実装をしないが、本物には以下のような要素もある
 ** 右クリックで「旗」を立てられる
 ** マウスのボタンを2つ同時にクリックすると、そのマス目の周囲をクリックしたことになる
 ** 最初にクリックしたマス目は爆弾にならない
 *** 当初のWindows版にはあるが、そうでないケースもあり、イライラさせられる

要素が分かったら、それを「実装」する

 * implement ... 実装する
 * implementation ... 実装 (実装した結果、どうやって実装したか)

=== 「実装」する場合、どのような要素が必要か

「ゲームの流れ」を考えながら、何が必要かを考えてみる。

 * ゲームの最初に爆弾がどこにあるかを決める
 ** ユーザに「爆弾が見えない」格子状の画面を表示する
 ** 盤面のサイズは、今回は8x8固定とする。
 * 爆弾の数も改めて決めておく必要がある。（今回は二日目に決める）
 ** 爆弾の配置も固定とする
 ** ひと通り実装した後に「ランダム」に配置する方法を考えてみる
 * ユーザのクリックに応じて以下のような反応をする
 ** 爆弾でなければ開く
 ** 全部開いたら「クリア」、爆弾なら「ゲームオーバー」
 * 「終了」（「ゲームオーバー」）の後、それをユーザに伝える
 ** 「終了」の条件1: 爆弾をクリックした
 ** 「終了」の条件2: 爆弾以外の全てのマス目を開いた
 * 次のゲームを開始できるように、リセットボタンを表示しておくのはどうだろうか。
 ** リセットボタンを押したら、盤面をリセットして最初に戻る。
 ** 本家のマインスイーパは顔の部分がリセットボタンになっている。
 * 旗や両ボタンクリックは今回はサポートしないことにする。

ちなみに、スマホでは「終了」ボタンは要らないので仕様で考える必要もない。
（但し「中断」については考える必要があるかもしれない）

== サンプルプロジェクトを実行する（@<code>{MainActivityDay1_0_Start.java}）

目標（「マインスイーパを作る」）を見た上で、
まず最初にサンプルプロジェクトを動作させることから始める。

ダウンロードしたサンプルプロジェクトの
@<code>{src/AndroidQuickTraining} フォルダ配下に、
今回のアプリを開発する上で必要な全てが入っている。
このプロジェクトをEclipseにインポートすることから始める。

 * Eclipseへのインポート方法
  * File -> New -> Project.. を選択
  * Androidフォルダの Android Project from Existing Code を選択
  * Browse ボタンを押し、サンプルプロジェクトのフォルダを選択して OK
  * src/AndroidQuickTraining を選択して Finish
 * 注意: Android 4.4.2とエミュレータ用の仮想デバイスを準備しておくこと
 ** 詳細な説明は省略する……

//image[sdk-and-virtual-device-manager-mod][SDKマネージャと仮想デバイスマネージャ][]{
//}

 * 実行方法
 ** Run -> Run
 ** プロジェクトフォルダを右クリックでも良い（@<img>{run-as-android-application}）

//image[run-as-android-application][サンプルプロジェクトを実行する][]{
//}


=== 参考: 使用するツールについて
==== Eclipse

 * @<href>{http://goo.gl/qNvb3J} (統合開発環境 - Wikipedia)
 * 統合開発環境: ソフトウェア開発に必要な複数のツールをまとめたソフトウェア
 ** エディタ: 何かを編集するためのソフト。メモ帳のお化けみたいなもの
 ** コンパイラ: ソースコードから実際のソフトウェアとして動作する実行コードを生成するもの
 ** デバッガ: ぼっこわれた時にどこが壊れたか、どうやって壊れたかを調べる (デバッグ) ためのツール
 * 便利機能がたくさんある -> 技術者はエディタの機能に慣れたり、機能を追加したりもする

==== Android SDK
 * Androidのソフトウェア開発を行うための「ソフトウェア開発キット」

==== ADT Plugin for Eclipse

 * Android Developer Tools
 * Eclipseは色々なソフトウェア開発に使う
 * Android SDKとセットで用意することで「Eclipse上でAndroidアプリの開発を行えるようにする」ツールとなる。

==== エミュレータ

 * パソコンの中でAndroidアプリを試しに実行出来る
 * emulator -> emulate = 模倣する、真似する
 * 色々制約がある
 ** 動作がとても遅い
 ** GPSやカメラといった機構を使いづらい
 ** etc.

 エミュレータは起動しっぱなしにしておこう

 * エミュレータ自体の起動が非常に遅い。人生は短い
 * なお、実機（本物のAndroid端末）を準備出来れば、直接実行することも可能

== サンプルプロジェクトの構造を眺める
==== @<code>{AndroidManifest.xml}

 * このアプリ全般に関する情報が記載されている
 ** アプリ名は何か
 ** アイコンに使う画像はどれか
 ** どういうAndroidデバイスにインストールしてもいいのか
 ** 端末のどういう機能を使ってもいいのか（Permission）
 * XML（Extensible Markup Language、「えっくすえむえる」と読む）形式で記述されている
 ** XMLという形式自体はAndroidやスマホとは関係なく一般的に使われる
 ** 後述するレイアウトファイルも全てこの形式で記述する
 ** Webページを記述するHTMLと似ている
 * 「Manifest」
 ** 一般的には「積荷証明書」「声明書」といった意味。
 *** 例1: 選挙公約 election manifest
 *** 例2: 共産党宣言 Communist Manifesto
 * 大統領風の人が「これからこのプログラムについての重要な情報を宣言する！」と言っていると想像する

==== Activity / Fragment

 * 画面を表示するための機能。
 ** 今回のアプリは、実行中に一つの@<code>{Activity}、一つの@<code>{Fragment}だけを使用する
 * 今回のサンプルプロジェクトには@<code>{Activity}の実装が複数入っている@<img>{activities}
 ** トレーニングのステップに応じたファイルを入れてある

//image[activities][Activityの実装が階層化されたフォルダに含まれている][]{
//}

==== プロジェクトに関わるその他の要素

今回関係のあるものを説明しておく

===== @<code>{src/} フォルダ

 * ソースコード == javaファイルは個々に収まる
 * 一般的に、source code の一部を引っ張って"src"としてソースコードを収めることがよくある

===== @<code>{res/}フォルダ

 * リソース (resource) の略で、画像データや文字列データを保存する
 * Android端末の大きさに合わせて複数の画像データが必要になったりする。

===== @<code>{res/layout/}フォルダ

 * @<code>{res/}に含まれるリソースの中でも「レイアウト」と呼ばれるものを保存する。
 * @<href>{http://developer.android.com/intl/ja/guide/topics/resources/layout-resource.html}

== ここからの学習の進め方
=== 変更点を手動で入力する方法

理想的には、実際に自分で入力しながらステップ毎のファイルと比較する方法を採ると良い。
その場合は、@<code>{MainActivity.java}と@<code>{fragment_main.xml}の組を用いて演習を行う。

なお、@<code>{AndroidManifest.xml}は、サンプルプロジェクトをインストールした時点で
@<code>{MainActiivty.java}を利用する設定になっている。

//list[default_android_manifest_part][@<code>{AndroidManifest.xml}内で@<code>{Activity}が指定されている箇所]{
<activity
    android:name="com.example.training.MainActivity"
    android:label="@string/app_name" >
  <intent-filter>
    <action android:name="android.intent.action.MAIN" />
    <category android:name="android.intent.category.LAUNCHER" />
  </intent-filter>
</activity>
//}

@<code>{MainActivity.java}も@<code>{fragment_main.xml}を参照する状態になっている。

//list[how_to_change_layout][@<code>{Activity}内でレイアウトが指定されている箇所]{
@Override
public View onCreateView(LayoutInflater inflater, ViewGroup container,
                         Bundle savedInstanceState) {
  View rootView = inflater.inflate(R.layout.mine_fragment_day1_1_show_1_button, container,
      false);
    return rootView;
  }
//}

先に進めなくなった場合、Eclipse上で各チェックポイントとなる
@<code>{Activity}ファイルを@<code>{AndroidManifest.xml}に指定することで、
該当するステップにおける動作を確認することが出来る。

レイアウトの編集に躓いた場合、@<code>{MainActivity.java}で指定されているレイアウトを、
各ステップのレイアウトファイルに変えてみると良い。

なお、@<code>{MainActivity.java}と@<code>{MainActivityDay1_0_Start.java}は、
サンプルプロジェクトのダウンロード時点では（Javaのクラス名を除いて）一致している。
同様に@<code>{fragment_main.xml}と@<code>{mine_fragment_day1_0.xml}も、
サンプルプロジェクトのダウンロード時点では内容が同じになっている。

=== 変更点をチェックポイント毎に追う方法

@<code>{AndroidManifest.xml}で使用する@<code>{Activity}をチェックポイントの実装に切り替えることで、
本トレーニングの動作をステップごとに確認出来る。
@<code>{android:name=""}のダブルクオート内を適切に変更すること。

（この方法で速習を行う場合、レイアウトファイルの設定を変更する必要はない）

//list[use_day2_0_start][@<code>{AndroidManifest.xml}内で二日目冒頭の@<code>{Activity}を参照する例]{
<activity
    android:name="com.example.training.MainActivityDay2_0_Start"
    android:label="@string/app_name" >
  <intent-filter>
    <action android:name="android.intent.action.MAIN" />
    <category android:name="android.intent.category.LAUNCHER" />
  </intent-filter>
</activity>
//}


=== トレーニング中の注意事項

 * 非常に「たくさん」あるが、一部を説明する。
 * 今回のトレーニングを行う場合には、行き詰まった際にサポートになる人がいたほうが良い。

==== 「空白」「改行」「全角文字」「大文字・小文字」「l, 1, L」等の違いに注意

特にブログやWord等で文字を入力しているだけのケースでは意識しないが、
プログラミングにおいてはこれらの文字は意味が全く異なる。

 * 特に「全角文字」はプログラム中ではほぼ「エラー」になる
 ** ユーザに表示する文字を入力するケースは例外
 * 1, l, Lといった違いにも注意。ほぼ「エラー」になる
 * おまけ: @<href>{http://ja.wikipedia.org/wiki/Whitespace}
 ** Whitespaceは「空白」に相当する文字の違いで命令を行うプログラミング言語
 ** 真っ白なプログラム: @<href>{http://compsoc.dur.ac.uk/whitespace/count.ws}

==== Javaの@<code>{import}に注意

本編ではしばしば省略されているが、「パッケージ」の指定が必要なケースが多々ある。
具体的には、コードを追加する際、@<code>{Activity}ファイルの冒頭の@<code>{import}を追加する必要が発生するケースで、この文章ではしばしばその指摘が（不適切に）省略されていることがある。

例として、後半の「イベントリスナー」を登録する部分で@<list>{no_listener}を@<list>{with_listener}
とするケースを挙げる。

//list[no_listener][変更前]{
public static class PlaceholderFragment extends Fragment {
  public PlaceholderFragment() {
  }

  @Override
  public View onCreateView(LayoutInflater inflater, ViewGroup container,
      Bundle savedInstanceState) {
    View rootView = inflater.inflate(R.layout.main_fragment, container, false);
    return rootView;
  }
}
//}

//list[with_listener][変更後]{
public static class PlaceholderFragment extends Fragment implements OnClickListener {
  public PlaceholderFragment() {
  }

  @Override
  public View onCreateView(LayoutInflater inflater, ViewGroup container,
      Bundle savedInstanceState) {
    View rootView = inflater.inflate(R.layout.main_fragment, container, false);
    Button button00 = (Button) rootView.findViewById(R.id.button00);
    button00.setOnClickListener(this);

    return rootView;
  }

  @Override
  public void onClick(View v) {
    Log.d("test", "Clicked!");
  }
}
//}

一見すると、このファイルへの変更はこれで終了に見えるが、
実は@<code>{import}が並んでいる前半にも変更が必要であったりする。

//list[no_listener_import][変更前の@<code>{import}部分]{
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.app.ActionBarActivity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
//}

//list[with_listener_import][変更後の@<code>{import}部分。3行追加がある]{
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;                            <--- 暗黙のうちに追加
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;           <--- 暗黙のうちに追加
import android.view.ViewGroup;
import android.widget.Button;                       <--- 暗黙のうちに追加
//}

Eclipse上での簡単な対策の一つは、キーボード上で@<code>{Ctrl-Shift-O}を実行すること。
自動的に不足している@<code>{import}行を補完してくれる。

 * 参考: @<href>{http://dev.chrisryu.com/2007/01/eclipse10.html}


==== 「提供元不明のアプリ」（実機を利用してアプリを実行する場合）

開発中のアプリを実機にインストールする場合、
設定画面「提供元不明のアプリ」にチェックを入れる必要がある。@<img>{untrusted-source}

//image[untrusted-source][提供元不明のアプリ][scale=0.2]{
//}

 * 開発中のアプリは、同じソースコードを使っても、デバイスから「信頼」はされていない
 ** 言ってみれば不正ソフトウェアにちょっと近い領域のアプリ
 ** 「信頼されている」とは、すなわち「署名されている」アプリのこと
 ** 「署名」 ... アプリ開発で印鑑を押すようなもの。今回は省略
 *** 正式にGoogleのWebサイト上で販売したりする場合は必須になる
 * 注意: これを行うと、Googleの公式マーケット以外から提供された危険なアプリをインストールしても気づかない

=== 参考: プログラマはインデックスを「0から始める」のがお好き

 * index .. 索引
 * 配列の最初の要素をarray[0]（0-origin）とするか、array[1]（1-origin）とするか
 ** 慣習に若干近い……

実は実生活では無意識に両方混ぜて使っている。

//quote{
複数のオリジンが混在する身近な例として、日時があげられる。
年・月・日は1オリジンであるが、時・分・秒は0オリジンである。
（@<href>{http://goo.gl/NMhrsE} オリジン - Wikipedia）
//}

 * origin ... 起源、源泉、先祖、血統、家柄
 ** origin of civilization で「文明の起源」
 * Androidアプリで使われるJava言語では 0-origin。つまり0から始まる
 * 今回は全く関係ないがメモリアドレスに関わる計算をする際の名残？と考えると分かりやすい
 ** addr+0 は先頭 (今ではlst[1]が最初でも不整合は生じない)

サンプルプロジェクトのファイル名でも、1-originと0-originが混ざってしまっている。


== アプリにボタンを1つ配置する（@<code>{MainActivityDay1_1_Show1Button.java}）

最初に、"Hello World"という文字列が表示されている画面に、
代わりに"Hello World"という文字列が表示されたボタン一つを配置する。

初期状態は以下の通り。

//list[mine_fragment_day1_0][最初のレイアウト（@<code>{layout/mine_fragment_day1_0.xml}）]{
<RelativeLayout xmlns:android="http://schemas.android.com/apk/res/android"
  xmlns:tools="http://schemas.android.com/tools"
  android:layout_width="match_parent"
  android:layout_height="match_parent"
  android:paddingBottom="@dimen/activity_vertical_margin"
  android:paddingLeft="@dimen/activity_horizontal_margin"
  android:paddingRight="@dimen/activity_horizontal_margin"
  android:paddingTop="@dimen/activity_vertical_margin"
  tools:context="com.example.training.MainActivity$PlaceholderFragment" >

  <TextView
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:text="@string/hello_world" />

</RelativeLayout>
//}

これを、以下のように変更する。（@<code>{layout/mine_fragment_day1_1_show_1_button.xml}）

//list[mine_fragment_day1_1][@<code>{layout/mine_fragment_day1_1_show_1_button.xml}]{
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:paddingBottom="@dimen/activity_vertical_margin"
    android:paddingLeft="@dimen/activity_horizontal_margin"
    android:paddingRight="@dimen/activity_horizontal_margin"
    android:paddingTop="@dimen/activity_vertical_margin"
    tools:context="jp.ascii.training2014.MainActivity$PlaceholderFragment" >

    <Button
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="@string/hello_world" />

</LinearLayout>
//}


=== レイアウトとは何か

 * 「どう部品が配置されるか」を指定する
 ** 「家具のレイアウト」とニュアンスは同じ。
 * アプリ内でレイアウトを指定すると、Android OS本体がその指定どおりに部品を表示する
 * 「レイアウトエディタ」 ... 「レイアウト」を編集するツール (復習: 「エディタ」)
 * @<code>{AndroidManifest.xml}に続いて、XML形式のファイルを再び変更する

==== @<code>{res/layout/}について

 * このフォルダの配下にレイアウト設定ファイルがある
 * レイアウト設定ファイルに「部品」を配置する

==== 今回用いるレイアウト用の部品について

 * 個々の「部品」（パーツ）は「ウィジェット」とか@<code>{View}とも呼ばれる
 ** 今回は「部品」とだけ覚えておけば良い
 * @<code>{LinearLayout} ... 横並び、縦並びに配置する
 ** Linear: 「直線の」「まっすぐ」
 *** 「リニアモーターカー」のリニア
 * @<code>{Button} ... ユーザが押せるボタンを配置する
 ** 今回の8x8のマス目を構成する
 * @<code>{TextView} ... 文字列を表示する
 ** メッセージの表示に使える

=== @<code>{LinearLayout}を配置する

@<code>{LinearLayout}を配置するため、
レイアウトを記述したXML（Extensible Markup Language、「えっくすえむえる」と読む）を編集する。

 * @<code>{LinearLayout}にとりあえず変更します。
 ** 「横に並べる」「縦に並べる」だけであればこちらの方がはるかに楽なため
 * （もともとプロジェクトに@<code>{RelativeLayout}は使いません
 * 「レイアウトエディタ」というものが便利です
 ** @<href>{http://goo.gl/wzI058}（エディタ - Wikipedia）

=== ボタン（@<code>{Button}）を配置する

（チェックポイント: MainActivityDay1_1_Show1Button.java）

 * @<code>{TextView}を@<code>{Button}へ変更する
 * このボタン大きすぎね？
 ** レイアウトエディタで遊んでみましょう
 * テキストを編集してみます。

=== 参考: 「エラー」と「警告」に注意

 * 「エラー」: 「そ　れ　で　は　う　ご　き　ま　せ　ん」
 * 「警告」: 「こんなことやってると、後で痛い目見るよ」
 * 例
 ** @<code>{LinearLayout}のタイポを混入 -> エラー
 ** @<code>{@string/hello_world} を別の文字列に変えてしまう -> 警告
 * エラーは直さなければ動作しない
 * 警告は、動作はするものの、推奨されず、意図しない動作をすることが非常に多い
 ** 色々な理由で起こるが、理由なしに無視をしないほうが良い

== ボタン（@<code>{Button}）を8つ並べる (MainActivityDay1_2_Show8Buttons.java)

 * 8つ並べる
 * @<code>{LinearLayout}が「横に並べる」

== ボタンを8x8の格子状に並べる (MainActivityDay1_3_Show88Buttons.java)

8x8の格子状にボタンを配置するには、今度は縦に@<code>{LinearLayout}を並べることになる。

 * 復習: @<code>{LinearLayout} ... 横並び、縦並びに配置してください
 * @<code>{LinearLayout} は別の@<code>{LinearLayout}を並べるのにも使える
 * ボタンを8つ持つ@<code>{LinearLayout}を8つ並べる


 * 注意: レイアウトを記述したXMLのトップレベルの部品（今回は最初の@<code>{LinearLayout}）には特別な意味がある
 ** 注意してレイアウトを重ねること

=== @<code>{LinearLayout}と@<code>{Button}のサイズや意味を変更する

 * XMLの@<code>{<こういうの>}を「タグ」、その中の@<code>{something=""}というのを「属性」と呼ぶ
 ** 参考: @<href>{http://www.atmarkit.co.jp/aig/01xml/attribute.html}
 * 属性を変更することで、「部品」の動作を詳細に記述する
 * 今回把握しておくべき属性
 ** @<code>{android:layout_width}, @<code>{android:layout_height}
 ** @<code>{android:minWidth}, @<code>{android:minWidth}
 ** @<code>{android:orientation}（@<code>{LinearLayout}で使う）
 *** orientation ... 方向
 *** 「横並び」なのか「縦並び」なのかを@<code>{orientation}という属性で指定することが出来る
 *** 「並び」が影響するのは今回は@<code>{LinearLayout}だけ
 *** 何も指定していない状況では横並びになる。
 ** @<code>{android:id} ... 今は各ボタンに重複なく割り当てられていればOK
 *** サンプルプロジェクトでは@<code>{@+id/buttonXY}（X座標とY座標）としている

=== 8x8のボタンを配置する際の「コピペ作業」での注意

 * 8x8のボタンを配置する際、いわゆる「コピペ」作業が発生する
 * プログラミングでは、一般的に「コピペ」は良くないとされる
 * 何故？
 ** 重複しては行けない情報が重複する
 ** 意味が分かってないことが多い
 ** 「コピペ」で出来るのならおそらく「自動化」出来る
 *** 素早く作業するのであれば自動化に勝る高速化はない
 * そして実際、今回コピペ作業をすると、リソースIDの部分が重複する。

=== リソースID

 * リソースID ... レイアウト中の各部品を特定するためのID
 ** ID ... identifier（この表現自体は一般的なはず）
 ** 特にプログラミングにおいて、日本語では「識別子」と呼ばれることも
 * 各部品（@<code>{LinearLayout}, @<code>{TextView}, @<code>{Button}）に@<code>{android:id=""}の形で指定している

=== 今回のレイアウトファイルでのリソースIDの振り方ルール

 * @<code>{@+id/buttonXY} というルールを使っている
 ** XとYはボタンの「座標」を「0-origin」になっている
 ** 復習: 0-origin ... 0から数え始める。@<code>{buttonXY}なら左からX+1番目、上からY+1番目
 * 例1: @<code>{android:id="@+id/button00"}
 ** 「8x8のボタン群の一番左上のボタンのIDは@<code>{button00}」
 * 例2: @<code>{android:id="@+id/button34"}
 ** 「8x8のボタン群の左から4番め、上から5番目のボタンのIDは@<code>{button34}」

コピペ作業では、コピー&ペーストの後にこのIDの変換作業が発生するため、
@<code>{mine_fragment_day1_3_show_88_buttons.xml}をコピーしてしまう方が効率的。

//list[table_again][マインスイーパの盤面のX,Yを並べる]{
| 00 | 10 | 20 | 30 | 40 | 50 | 60 | 70 |
| 01 | 11 | 21 | 31 | 41 | 51 | 61 | 71 |
| 02 | 12 | 22 | 32 | 42 | 52 | 62 | 72 |
| 03 | 13 | 23 | 33 | 43 | 53 | 63 | 73 |
| 04 | 14 | 24 | 34 | 44 | 54 | 64 | 74 |
| 05 | 15 | 25 | 35 | 45 | 55 | 65 | 75 |
| 06 | 16 | 26 | 36 | 46 | 56 | 66 | 76 |
| 07 | 17 | 27 | 37 | 47 | 57 | 67 | 77 |
//}


==== 参考: @<code>{"@id/button00"}と@<code>{"@+id/button00"}の違いについて

 * @<code>{+}があるかないかで意味が異なる。
 * @<code>{@+id/button00}の意味: @<code>{button00}というIDは初出。アプリは新たに準備する必要がある。
 * 今回のリソースファイルでは全て@<code>{+}をつけているため、違いを意識する必要はない。
 * 参考: @<href>{http://developer.android.com/intl/ja/guide/topics/resources/layout-resource.html#idvalue}

===== なぜそんな違いがあるのか

本ドキュメントでは使用しないが、レイアウト部品@<code>{RelativeLayout}では@<code>{+}の有無は重要。

 * @<code>{RelativeLayout} ... 「この部品はこの部品の左に置く」といった「相対位置」を指定できる
 * relative ... 親戚、関係のある、相対的な

以下にAndroidの公式ドキュメント（@<href>{http://developer.android.com/intl/ja/guide/topics/ui/layout/relative.html}）の例を示す。

//list[example_of_relative_layout][@<code>{RelativeLayout}で@<code>{+}の有無をうまく使い分けている例]{
<?xml version="1.0" encoding="utf-8"?>
<RelativeLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="fill_parent"
    android:layout_height="fill_parent"
    android:paddingLeft="16dp"
    android:paddingRight="16dp" >
    <EditText
        android:id="@+id/name"
        android:layout_width="fill_parent"
        android:layout_height="wrap_content"
        android:hint="@string/reminder" />
    <Spinner
        android:id="@+id/dates"
        android:layout_width="0dp"
        android:layout_height="wrap_content"
        android:layout_below="@id/name"
        android:layout_alignParentLeft="true"
        android:layout_toLeftOf="@+id/times" />
    <Spinner
        android:id="@id/times"
        android:layout_width="96dp"
        android:layout_height="wrap_content"
        android:layout_below="@id/name"
        android:layout_alignParentRight="true" />
    <Button
        android:layout_width="96dp"
        android:layout_height="wrap_content"
        android:layout_below="@id/times"
        android:layout_alignParentRight="true"
        android:text="@string/done" />
</RelativeLayout>
//}

//image[sample-relativelayout][@<code>{RelativeLayout}の使用結果]{
//}

このレイアウトファイル自体は本トレーニングの範囲外の部品も使っているが、説明としては以下の通り。

 * 画面には「名前入力フィールド」「日付」「時刻」「送信」ボタンがある
 ** <code>{EditText}（「名前入力フィールド」）@<code>{Spinner}（「日付」と「時刻」のドロップダウン）
 * 「日付」と「時刻」は「名前入力フィールド」の下にあって欲しい、と考えている
 * そのために、@<code>{android:layout_below="@id/name"}を指定している
 ** 「相対的な位置」（英語で "relative" position）を指定している
 ** below ... （前置詞で）下に
 * この時、@<code>{+}は使用しない。
 ** 「名前入力フィールド」を示す@<code>{EditText}が既にそのIDを利用している
 ** 最初に登場したもの以外には@<code>{+}はつけてはいけない

== 見た目をよりマインスイーパーっぽくする（@<code>{MainActivityDay1_4_ShowBetter88Buttons.java}）

 * ボタンの見た目がなんかアレですね
 * 「デフォルト」 (標準) のボタンの見栄えが今回のマインスイーパーに合ってないからです
 * 標準のボタンの見栄えを変える必要があります。
 ** 今回は深入りしませんが……結構面倒です
 ** 9 patch とは？ pressed？ focused？ disabled？
 * プログラマーの日常
 ** わからない時には割とオンラインで聞いたりします
 * 今回は自分で用意した「隙間のないボタン用drawable」を使う
 ** 参考1: @<href>{http://qiita.com/amedama/items/fb94c9665a6f7a4e7676}
 ** 参考2: @<href>{https://github.com/dmiyakawa/crop_9patch_space}
 * 今はとりあえずログを出力してお茶を濁す
 ** クリックされた時に何か起きていることを示す！
 ** @<code>{android.util.Log} というパッケージがあります
 ** パッケージ ... Javaの概念。「名前空間」と呼ばれる概念と関係がある
 *** ここでは、ファイルを格納するフォルダ構造と同様なものと考えておく
 *** @<href>{http://goo.gl/idxKQf}（名前空間 - Wikipedia）


== ユーザがボタンを押したとき、アプリを反応させる（@<code>{MainActivityDay1_5_ButtonWithEvents.java}）
=== 現状: ボタンを押しても何も起こらない

 * 今のところ、レイアウトにボタンを配置しただけ。
 * 「ボタンを押した時」に「何かしてよ」とプログラムする必要がある。
 * 「どのボタン」が押されたとき「何をするか」を決める必要がある。

=== 「左上のボタン」が「押された」ときに何かする

 * 目標はそれぞれのボタンが押された時に「爆弾をクリックしたか」といったチェックをしたい
 * ステップを踏むため、まず「左上のボタン」だけに注目してみる
 * 座標で言うと@<code>{X=0, Y=0}
 * これを達成するために「イベント」について理解する必要がある。

=== 「イベント」と「イベントリスナー」

 * 「何かが起きたとき」の「何か」をAndroidでは特に「イベント」と言う
 * 「何か」が「起きたとき」を検知する仕組みを「イベントリスナー」と言う
 * 「ボタンを押したとき」も「イベント」
 * このイベントに対応するイベントリスナーを用意する。
 * イベントリスナーをイベントの発生源に登録する
 ** イベントの発生源は、今回は「左上のボタン」とする

==== @<code>{OnClickListener} ... 「イベントリスナー」を実現する仕組み

 * @<code>{onClick()}というメソッドを提供する
 ** on click ... 「ボタンを押したとき」
 * Javaの「インターフェース」の一つ。
 ** 「インターフェース」についての詳細な説明は省く
 * 今回は深く考えず、「イベントを処理するのに@<code>{OnClickListener}を使えば良い」と理解しとくのが吉
 * @<code>{On(なんとか)Listener}という名前は結構多い
 ** @<code>{OnLongClickListener} ... 長押しイベントを処理するのに使う
 ** @<code>{OnDragListener} ... ドラッグ&ドロップの「ドラッグ」イベントを処理するのに使う
 * 今回、全てのボタン関連のイベントを一つのイベントリスナーで処理することにする
 ** 別の方法として、それぞれのボタンイベントに対応したリスナーを用意する、という方法もあり得る。

=== 「左上のボタン」が「押された」ときの「イベント」に対処する「イベントリスナー」を用意する

 * ボタンが押された時に、とりあえずログに表示させてみる
 ** 目標は「ボタンが押された時に爆弾かどうかを判定する」といったこと。
 *** 二日目に実装する。
 ** ここでは、8x8のボタンの中で左上のボタンだけ反応するようにする。

//list[fragment_with_on_click][イベントリスナーとイベントハンドラを備えた実装]{
// 最初にandroid.util.Log パッケージをインポートしておくこと。
// （org.apache.common.logging.Logではない）
import android.util.Log;

.. (中略) ..

public static class PlaceholderFragment extends Fragment implements OnClickListener {
  public PlaceholderFragment() {
  }

  @Override
  public View onCreateView(LayoutInflater inflater, ViewGroup container,
         Bundle savedInstanceState) {
    // 注意: 使用するレイアウトファイルは適切に指定すること
    View rootView = inflater.inflate(R.layout.fragment_main, container, false);
    Button button00 = (Button) rootView.findViewById(R.id.button00);
    button00.setOnClickListener(this);

    return rootView;
  }

  @Override
  public void onClick(View v) {
    Log.d("test", "Clicked!");
  }
}
//}

==== 左上のボタンを探す

@<list>{fragment_with_on_click}内で「左上のボタン」を探しているのは以下の場所。

//list[fragment_with_on_click_button_part1][左上のボタンを探す]{
View rootView = inflater.inflate(R.layout.fragment_main, container, false);
Button button00 = (Button) rootView.findViewById(R.id.button00);
//}

 * @<code>{rootView}はレイアウトファイルの根っこ（ルート）の@<code>{View}（部品）
 * @<code>{rootView}からレイアウトファイルの木構造をたどって、左上のボタンを@<code>{button00}としている。
 ** @<code>{R.id.button00}はレイアウトファイルの@<code>{@+id/button00}に対応している。
 ** プログラム中でリソースIDを指定する場合には@<code>{R.id.}をIDの前につけること

//list[buttons00_in_layout][@<code>{R.id.button00}に対応するレイアウトファイルの一部]{
<Button
  android:id="@+id/button00"          <-------------- ここに対応している
  android:layout_width="wrap_content"
  android:layout_height="wrap_content"
  android:minHeight="40dip"
  android:minWidth="40dip" />
//}

==== 左上のボタンに「イベントリスナー」を登録する

//list[fragment_with_on_click_button_part2][左上のボタンにイベントリスナーを登録する]{
button00.setOnClickListener(this);
//}

==== 「イベントリスナー」が「イベント」を取得したときに「何か」する

 * 今回はAndroidのログに記録してみる
 * @<code>{Log.d()}をもちいる

//list[fragment_with_on_click_button_part3][なにかする]{
@Override
public void onClick(View v) {
  Log.d("test", "Clicked!");
}
//}

 * Eclipseの「DDMSパースペクティブ」を利用してログを見ることが出来る
 * 特に関係するのはApplicationが@<code>{com.example.training}となっている場所

//image[ddms-example1][DDMS画面でClicked!が表示されている様子]{
//}

== 一日目、おわりに

 * 紹介した機能は大きく分ければ2つ
  * 「レイアウト」
  * 「イベント」
 * 仕様をもう一度見直す
  * ボタンを押したときに何が起こるのか
  * ゲームの終了条件は
  * リセットボタン？
 * 目標: 「マインスイーパを作る」

=== おまけ

 * @<href>{https://github.com/dmiyakawa/u-i-ha-ru-}（「うーいーはーるー」と読む）
 ** 今回利用している@<code>{LinearLayout}と@<code>{Button}だけでお絵かきをする
 ** 実用には堪えない

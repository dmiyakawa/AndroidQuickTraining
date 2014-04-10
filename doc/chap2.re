= 二日目
== Fragment を二日目開始時のものに変更し、動作させる

 * 今日使いやすいようにレイアウトを少し変えてあります
 * (meld 等でグラフィカルに差分を表示してみせる)
 * ツール類はこういう時便利です

== 全てのボタンにイベントリスナーを設定する

 * 昨日は左上のボタンだけでした
 * 全部のボタンにイベントを登録するには
  1. 一つ一つ丁寧にボタンにイベントリスナーを登録する
  1. 自動でやらせる
 * 2つめにチャレンジしてみることにする。
 ** @<code>{LinearLayout}の「子供」に@<code>{LinearLayout}があり……
 ** その「子供」(つまり「孫」)に@<code>{Button}があるのだった
 ** 「子供の子供がボタンだったらイベントを登録する」ってプログラムに書けないのか？
 ** 書けます
 ** 注意として……「子供」には@<code>{LinearLayout}以外も含まれています。
 *** @<code>{Button}と@<code>{TextView}は無視しよう
 *** @<code>{instanceof} ... instance of ... そのViewが実際にその「型」だったら
 **** @<code>{LinearLayout}だったら。
 *** 言葉の意味には深く立ち入りません
 **** オブジェクト指向における「オブジェクト == インスタンス」が特定のクラス派生のものであったら、という意味ですが

//list[logd][イベントリスナ]{
            LinearLayout rootView = (LinearLayout)
                    inflater.inflate(R.layout.mine_fragment_4_day2_start,
                    container, false);
            for (int index = 0; index < rootView.getChildCount(); index++) {
                View child = rootView.getChildAt(index);
                Log.d("test", "child: " + child);
                if (child instanceof LinearLayout) {
                    LinearLayout childAsLinearLayout = (LinearLayout) child;
                    for (int index2 = 0; index2 < childAsLinearLayout.getChildCount(); index2++) {
                        View grandchild = childAsLinearLayout.getChildAt(index2);
                        Log.d("test", "grandchild: " + grandchild);
                    }
                }
            }
//}

この結果として

//list[result_logd][結果]{
D/test    ( 1106): child: android.widget.TextView{b3dc2728 V.ED.... ......ID 0,0-0,0 #7f05007d app:id/textView1}
D/test    ( 1106): child: android.widget.LinearLayout{b3dc2c10 V.E..... ......I. 0,0-0,0}
D/test    ( 1106): grandchild: android.widget.Button{b3dc30d8 VFED..C. ......I. 0,0-0,0 #7f05003d app:id/button00}
D/test    ( 1106): grandchild: android.widget.Button{b3dc8db0 VFED..C. ......I. 0,0-0,0 #7f05003e app:id/button10}
D/test    ( 1106): grandchild: android.widget.Button{b3dc9790 VFED..C. ......I. 0,0-0,0 #7f05003f app:id/button20}
D/test    ( 1106): grandchild: android.widget.Button{b3dca170 VFED..C. ......I. 0,0-0,0 #7f050040 app:id/button30}
D/test    ( 1106): grandchild: android.widget.Button{b3dcab50 VFED..C. ......I. 0,0-0,0 #7f050041 app:id/button40}
D/test    ( 1106): grandchild: android.widget.Button{b3dcb530 VFED..C. ......I. 0,0-0,0 #7f050042 app:id/button50}
D/test    ( 1106): grandchild: android.widget.Button{b3dcbf10 VFED..C. ......I. 0,0-0,0 #7f050043 app:id/button60}
D/test    ( 1106): grandchild: android.widget.Button{b3dcc8f0 VFED..C. ......I. 0,0-0,0 #7f050044 app:id/button70}
D/test    ( 1106): child: android.widget.LinearLayout{b3dcd310 V.E..... ......I. 0,0-0,0}
D/test    ( 1106): grandchild: android.widget.Button{b3dcd668 VFED..C. ......I. 0,0-0,0 #7f050045 app:id/button01}
D/test    ( 1106): grandchild: android.widget.Button{b3dce048 VFED..C. ......I. 0,0-0,0 #7f050046 app:id/button11}
D/test    ( 1106): grandchild: android.widget.Button{b3dcea28 VFED..C. ......I. 0,0-0,0 #7f050047 app:id/button21}
D/test    ( 1106): grandchild: android.widget.Button{b3dcf408 VFED..C. ......I. 0,0-0,0 #7f050048 app:id/button31}
D/test    ( 1106): grandchild: android.widget.Button{b3dcfde8 VFED..C. ......I. 0,0-0,0 #7f050049 app:id/button41}
D/test    ( 1106): grandchild: android.widget.Button{b3dd07c8 VFED..C. ......I. 0,0-0,0 #7f05004a app:id/button51}
D/test    ( 1106): grandchild: android.widget.Button{b3dd11a8 VFED..C. ......I. 0,0-0,0 #7f05004b app:id/button61}
D/test    ( 1106): grandchild: android.widget.Button{b3dd1b88 VFED..C. ......I. 0,0-0,0 #7f05004c app:id/button71}
D/test    ( 1106): child: android.widget.LinearLayout{b3dd25a8 V.E..... ......I. 0,0-0,0}
D/test    ( 1106): grandchild: android.widget.Button{b3dd2900 VFED..C. ......I. 0,0-0,0 #7f05004d app:id/button02}
D/test    ( 1106): grandchild: android.widget.Button{b3dd32e0 VFED..C. ......I. 0,0-0,0 #7f05004e app:id/button12}
D/test    ( 1106): grandchild: android.widget.Button{b3dd3cc0 VFED..C. ......I. 0,0-0,0 #7f05004f app:id/button22}
D/test    ( 1106): grandchild: android.widget.Button{b3dd46a0 VFED..C. ......I. 0,0-0,0 #7f050050 app:id/button32}
D/test    ( 1106): grandchild: android.widget.Button{b3dd5080 VFED..C. ......I. 0,0-0,0 #7f050051 app:id/button42}
D/test    ( 1106): grandchild: android.widget.Button{b3dd5a60 VFED..C. ......I. 0,0-0,0 #7f050052 app:id/button52}
D/test    ( 1106): grandchild: android.widget.Button{b3dd6440 VFED..C. ......I. 0,0-0,0 #7f050053 app:id/button62}
D/test    ( 1106): grandchild: android.widget.Button{b3dd6e20 VFED..C. ......I. 0,0-0,0 #7f050054 app:id/button72}
D/test    ( 1106): child: android.widget.LinearLayout{b3dd7840 V.E..... ......I. 0,0-0,0}
D/test    ( 1106): grandchild: android.widget.Button{b3dd7b98 VFED..C. ......I. 0,0-0,0 #7f050055 app:id/button03}
D/test    ( 1106): grandchild: android.widget.Button{b3dd8578 VFED..C. ......I. 0,0-0,0 #7f050056 app:id/button13}
D/test    ( 1106): grandchild: android.widget.Button{b3dd8f58 VFED..C. ......I. 0,0-0,0 #7f050057 app:id/button23}
D/test    ( 1106): grandchild: android.widget.Button{b3dd9938 VFED..C. ......I. 0,0-0,0 #7f050058 app:id/button33}
D/test    ( 1106): grandchild: android.widget.Button{b3dda318 VFED..C. ......I. 0,0-0,0 #7f050059 app:id/button43}
D/test    ( 1106): grandchild: android.widget.Button{b3ddacf8 VFED..C. ......I. 0,0-0,0 #7f05005a app:id/button53}
D/test    ( 1106): grandchild: android.widget.Button{b3ddb6d8 VFED..C. ......I. 0,0-0,0 #7f05005b app:id/button63}
D/test    ( 1106): grandchild: android.widget.Button{b3ddc0b8 VFED..C. ......I. 0,0-0,0 #7f05005c app:id/button73}
D/test    ( 1106): child: android.widget.LinearLayout{b3ddcad8 V.E..... ......I. 0,0-0,0}
D/test    ( 1106): grandchild: android.widget.Button{b3ddce30 VFED..C. ......I. 0,0-0,0 #7f05005d app:id/button04}
D/test    ( 1106): grandchild: android.widget.Button{b3ddd810 VFED..C. ......I. 0,0-0,0 #7f05005e app:id/button14}
D/test    ( 1106): grandchild: android.widget.Button{b3dde1f0 VFED..C. ......I. 0,0-0,0 #7f05005f app:id/button24}
D/test    ( 1106): grandchild: android.widget.Button{b3ddebd0 VFED..C. ......I. 0,0-0,0 #7f050060 app:id/button34}
D/test    ( 1106): grandchild: android.widget.Button{b3ddf5b0 VFED..C. ......I. 0,0-0,0 #7f050061 app:id/button44}
D/test    ( 1106): grandchild: android.widget.Button{b3ddff90 VFED..C. ......I. 0,0-0,0 #7f050062 app:id/button54}
D/test    ( 1106): grandchild: android.widget.Button{b3de0970 VFED..C. ......I. 0,0-0,0 #7f050063 app:id/button64}
D/test    ( 1106): grandchild: android.widget.Button{b3de1350 VFED..C. ......I. 0,0-0,0 #7f050064 app:id/button74}
D/test    ( 1106): child: android.widget.LinearLayout{b3de1d70 V.E..... ......I. 0,0-0,0}
D/test    ( 1106): grandchild: android.widget.Button{b3de20c8 VFED..C. ......I. 0,0-0,0 #7f050065 app:id/button05}
D/test    ( 1106): grandchild: android.widget.Button{b3de2aa8 VFED..C. ......I. 0,0-0,0 #7f050066 app:id/button15}
D/test    ( 1106): grandchild: android.widget.Button{b3de3488 VFED..C. ......I. 0,0-0,0 #7f050067 app:id/button25}
D/test    ( 1106): grandchild: android.widget.Button{b3de3e68 VFED..C. ......I. 0,0-0,0 #7f050068 app:id/button35}
D/test    ( 1106): grandchild: android.widget.Button{b3de4848 VFED..C. ......I. 0,0-0,0 #7f050069 app:id/button45}
D/test    ( 1106): grandchild: android.widget.Button{b3de5228 VFED..C. ......I. 0,0-0,0 #7f05006a app:id/button55}
D/test    ( 1106): grandchild: android.widget.Button{b3de5c08 VFED..C. ......I. 0,0-0,0 #7f05006b app:id/button65}
D/test    ( 1106): grandchild: android.widget.Button{b3de65e8 VFED..C. ......I. 0,0-0,0 #7f05006c app:id/button75}
D/test    ( 1106): child: android.widget.LinearLayout{b3de7008 V.E..... ......I. 0,0-0,0}
D/test    ( 1106): grandchild: android.widget.Button{b3de7360 VFED..C. ......I. 0,0-0,0 #7f05006d app:id/button06}
D/test    ( 1106): grandchild: android.widget.Button{b3de7d40 VFED..C. ......I. 0,0-0,0 #7f05006e app:id/button16}
D/test    ( 1106): grandchild: android.widget.Button{b3de8720 VFED..C. ......I. 0,0-0,0 #7f05006f app:id/button26}
D/test    ( 1106): grandchild: android.widget.Button{b3de9100 VFED..C. ......I. 0,0-0,0 #7f050070 app:id/button36}
D/test    ( 1106): grandchild: android.widget.Button{b3de9ae0 VFED..C. ......I. 0,0-0,0 #7f050071 app:id/button46}
D/test    ( 1106): grandchild: android.widget.Button{b3dea4c0 VFED..C. ......I. 0,0-0,0 #7f050072 app:id/button56}
D/test    ( 1106): grandchild: android.widget.Button{b3deaea0 VFED..C. ......I. 0,0-0,0 #7f050073 app:id/button66}
D/test    ( 1106): grandchild: android.widget.Button{b3deb880 VFED..C. ......I. 0,0-0,0 #7f050074 app:id/button76}
D/test    ( 1106): child: android.widget.LinearLayout{b3dec2a0 V.E..... ......I. 0,0-0,0}
D/test    ( 1106): grandchild: android.widget.Button{b3dec5f8 VFED..C. ......I. 0,0-0,0 #7f050075 app:id/button07}
D/test    ( 1106): grandchild: android.widget.Button{b3decfd8 VFED..C. ......I. 0,0-0,0 #7f050076 app:id/button17}
D/test    ( 1106): grandchild: android.widget.Button{b3ded9b8 VFED..C. ......I. 0,0-0,0 #7f050077 app:id/button27}
D/test    ( 1106): grandchild: android.widget.Button{b3dee398 VFED..C. ......I. 0,0-0,0 #7f050078 app:id/button37}
D/test    ( 1106): grandchild: android.widget.Button{b3deed78 VFED..C. ......I. 0,0-0,0 #7f050079 app:id/button47}
D/test    ( 1106): grandchild: android.widget.Button{b3def758 VFED..C. ......I. 0,0-0,0 #7f05007a app:id/button57}
D/test    ( 1106): grandchild: android.widget.Button{b3df0138 VFED..C. ......I. 0,0-0,0 #7f05007b app:id/button67}
D/test    ( 1106): grandchild: android.widget.Button{b3df0b18 VFED..C. ......I. 0,0-0,0 #7f05007c app:id/button77}
D/test    ( 1106): child: android.widget.Button{b3df1538 VFED..C. ......I. 0,0-0,0 #7f05007e app:id/button1}
//}


 * わかりづらいですが…… @<code>{Button} が全部来ているのは間違いないようです！

//list[button_clicked][hoge]{
            LinearLayout rootView = (LinearLayout)
                    inflater.inflate(R.layout.mine_fragment_4_day2_start,
                    container, false);
            for (int index = 0; index < rootView.getChildCount(); index++) {
                View child = rootView.getChildAt(index);
                Log.d("test", "child: " + child);
                if (child instanceof LinearLayout) {
                    LinearLayout childAsLinearLayout = (LinearLayout) child;
                    for (int index2 = 0; index2 < childAsLinearLayout.getChildCount(); index2++) {
                        View grandchild = childAsLinearLayout.getChildAt(index2);
                        Log.d("test", "grandchild: " + grandchild);
                        if (grandchild instanceof Button) {
                            ((Button) grandchild).setOnClickListener(this);
                        }
                    }
                }
            }
//}

 * これでクリックしていることわ分かるんですが
 * 残念ながら「どれ」がクリックされたかが、分からない。
 * それがわからないと「爆弾を踏んだか」も分からない
 * かなしい。
 * というわけで、「座標」をログに表示させてみます


//list[cordinate][座標を表示する]{
        @Override
        public void onClick(View v) {
            // 関連するidを探します。ちなみに非常に酷い方法です
            boolean found = false;
            int view_x = -1;
            int view_y = -1;
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    if (mButtonIds[x][y] == v.getId()) {
                        found = true;
                        view_x = x;
                        view_y = y;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
            Log.d("test", "Clicked! x=" + view_x + ", y=" + view_y);
        }
//}

これでどのボタンがいつ押されたかが分かるようになりました

あなたは配列を駆使した高度なイベント処理をマスターしました

==== なぜ「酷い方法」なのか

 * 盤面のサイズが大きくなってきたときに全部見ていく
 ** 盤面が100x100だったら10000個比較。そのうち意味があるのは「あっても1つ」
 * 「ハッシュテーブル」

=== ゲーム画面を「初期化」する

 * 初期化 = Initialization ... 下準備
 * つまり、爆弾を配置する
 * 最初に: 前回の状態があったらそれをリセット
 ** 今回は「リセットボタン」がある
 ** 押したらここからスタート
 * 爆弾を「配置」する
 ** 覚えておく必要がある！

=== ゲームの動作を実装する
==== 爆弾をクリックしたら「爆」と表示する

 * とりあえずログに流してみよう

//list[baku][爆]{
       @Override
        public void onClick(View v) {
            // 関連するidを探します。ちなみに非常に酷い方法です
            boolean found = false;
            int view_x = -1;
            int view_y = -1;
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    if (mButtonIds[x][y] == v.getId()) {
                        found = true;
                        view_x = x;
                        view_y = y;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }

            if (mIsBomb[view_x][view_y]) {
                Log.d("test", "KA-BOOM!! x=" + view_x + ", y=" + view_y);          // <----- ここな
            } else {
                Log.d("test", "Clicked! x=" + view_x + ", y=" + view_y);
            }
        }

//}

==== 爆弾をクリックしなかったら「開」と表示する

 * (本当のマインスイーパーはここで「爆弾が全くないところでは展開する」をやりますが)
 * とりあえず何もなかった or 近くに爆弾あるぞ、だけ伝えることにしましょう。
 * とりあえず開いたら "開" と書きます。
 ** 爆弾だったら "爆" と書きます。ついでに色も赤くしてみましょう。
 *** この色の付け方は適切な方法とは実は言えません


//list[kai][開]{
            if (mIsBomb[view_x][view_y]) {
                Log.d("test", "KA-BOOM!! x=" + view_x + ", y=" + view_y);
                ((Button) v).setText("爆");
                ((Button) v).setTextColor(Color.RED);
            } else {
                Log.d("test", "Clicked! x=" + view_x + ", y=" + view_y);
                ((Button) v).setText("開");
            }
//}

==== 「これじゃヒントがないです(´・ω・`)」

 * 本当のマインスイーパーでは数字が出ます
 ** どのような数字だろうか……？

===== 「ヒント = 周囲の爆弾の数」を表示する「アルゴリズム」を考える

もう一度このテーブルと見比べてみる

//list[table_again][マインスイーパの盤面をもう一度]{
|| 00 || 10 || 20 || 30 || 40 || 50 || 60 || 70 ||
|| 01 || 11 || 21 || 31 || 41 || 51 || 61 || 71 ||
|| 02 || 12 || 22 || 32 || 42 || 52 || 62 || 72 ||
|| 03 || 13 || 23 || 33 || 43 || 53 || 63 || 73 ||
|| 04 || 14 || 24 || 34 || 44 || 54 || 64 || 74 ||
|| 05 || 15 || 25 || 35 || 45 || 55 || 65 || 75 ||
|| 06 || 16 || 26 || 36 || 46 || 56 || 66 || 76 ||
|| 07 || 17 || 27 || 37 || 47 || 57 || 67 || 77 ||
//}

 * 上と下がひっくり返ってることは注意 (プログラミングでかなりよくある)
 * 例えば「33」に注目すると
 ** 22, 32, 42, 23, 43, 24, 34, 35 のボタンが爆弾であるかを確認すればよい
 ** そのマス目の上下左右斜めの爆弾の数を調べる……
 ** @<code>{mIsBomb}の「上下左右斜め」を見れば良いのではないか……
 * もっと「一般的」に考える
 ** (x, y) として考えると……

|| x-1, y-1 || x, y-1 || x+1, y-1 ||
|| x-1, y || x, y (爆弾ではない) || x+1, y ||
|| x-1, y+1 || x, y+1 || x+1, y+1 ||

===== とりあえず左上・上・右上……と全部ロジックを並べてしまう

//list[logic][全部並べてしまう例]{
            if (mIsBomb[view_x][view_y]) {
                Log.d("test", "KA-BOOM!! x=" + view_x + ", y=" + view_y);
                ((Button) v).setText("爆");
                ((Button) v).setTextColor(Color.RED);
            } else {
                Log.d("test", "Clicked! x=" + view_x + ", y=" + view_y);
                // 上下左右斜めを調べる (間違い)
                int numOfBombs = 0;
                // 左上 
                if (mIsBomb[view_x-1][view_y-1]) {
                    numOfBombs = numOfBombs + 1;
                }
                // 上
                if (mIsBomb[view_x][view_y-1]) {
                    numOfBombs = numOfBombs + 1;
                }
                // 右上
                if (mIsBomb[view_x][view_y+1]) {
                    numOfBombs = numOfBombs + 1;
                }
                // 左
                if (mIsBomb[view_x-1][view_y]) {
                    numOfBombs = numOfBombs + 1;
                }
                // 中央は要らん :-)
                // 右
                if (mIsBomb[view_x+1][view_y]) {
                    numOfBombs = numOfBombs + 1;
                }
                // 左下
                if (mIsBomb[view_x-1][view_y+1]) {
                    numOfBombs = numOfBombs + 1;
                }
                // 下
                if (mIsBomb[view_x][view_y+1]) {
                    numOfBombs = numOfBombs + 1;
                }
                // 右下
                if (mIsBomb[view_x+1][view_y+1]) {
                    numOfBombs = numOfBombs + 1;
                }
                Log.d("test", "NumOfBombs for (" + view_x + ", " + view_y + "): " + numOfBombs);
                ((Button) v).setText(numOfBombs);
            }
//}

 * (ここで境界条件はまだクリックしないこと)

=== 「アプリが落ちたー！」

(ここで二箇所バグを入れています)

 1. Stringとintを取り違えた@<code>{setText()}
 1. 境界条件バグ

==== 「落ちた」とは

 * アプリケーションが「クラッシュした」とか「落ちた」とか言います
 * いわゆる「プログラムのバグ」です
 * 何が原因で落ちたのか？

==== 落ちた理由を調べてみよう、その1: setText(int)

 * ログで確認してみましょう
 ** @<code>{adb logcat}
 * 何か書いてありますね
 * (しかし理由はわからないかもしれない)
 * いきなりですみません。結構トリッキーなバグです。
 * @<code>{numOfBombs} は int です
 ** @<code>{setText(int)}のintは……別の意味なのです(´・ω・`)
 ** その数字を表示するのではなくて、その数字をIDに持つ登録されているメッセージを表示する
 * @<code>{numOfBombs} は@<code>{int}、ということで@<code>{String}に変換 (瑣末なので説明省略？)
 ** @<code>{((Button) v).setText(String.valueOf(numOfBombs));}

あなたはプログラミングの深淵の一つを覗きました

==== 落ちた理由を調べてみよう、その2: 配列の端っこと境界条件バグ

 * まだ落ちるぞ (境界条件)
 * 端っこで落ちるぞ (境界条件)
 * 理由を発見: 配列の外側にアクセスしてます
 * というわけで「端っこ」は注意
 ** これを「境界条件」とよく呼ぶ

==== ついでに: もっと簡単に書けますね -> (x-1〜x+1, y-1〜y+1)と指定するロジックを書く

 * 効率良く書くのもプログラマの仕事
 * ポイントは二つ
 ** 0未満と8以上は駄目
 ** 自分自身は決して爆弾ではない
 * 左上から右下までをループでチェックしてあげれば良い

//list[logic2][もう少しまともなロジック]{
    if (mIsBomb[view_x][view_y]) {
        Log.d("test", "KA-BOOM!! x=" + view_x + ", y=" + view_y);
        ((Button) v).setText("爆");
        ((Button) v).setTextColor(Color.RED);
    } else {
        Log.d("test", "Clicked! x=" + view_x + ", y=" + view_y);
        int numOfBombs = 0;
        for (int y = view_y - 1; y <= view_y + 1; y++) {
            if (y < 0 || y >= 8) {
                continue;
            }
            for (int x = view_x - 1; x <= view_x + 1; x++) {
                if (x < 0 || x >= 8) {
                    continue;
                }
                if (mIsBomb[x][y]) {
                    numOfBombs = numOfBombs + 1;
                }
            }
        }

        Log.d("test", "NumOfBombs for (" + view_x + ", " + view_y + "): " + numOfBombs);
        ((Button) v).setText(String.valueOf(numOfBombs));
    }
//}

あなたはマインスイーパーの作り方を学びました。

=== ゲームを「面白く」する処理を作りこむ

 * ゲームとしては一応動作します。
 ** 爆弾を避けていくゲーム

==== リセット

 * 色々細かい点を修正する必要があります。しかし大まかに言えば
 ** リセットボタンにイベントを登録してませんでした
 ** 書き込んだボタンの状態を元に戻してませんでした
 * 今回の実装では「状態のリセット」が(実は)案外大変です
 ** 詳しくは説明しません

 * 以下実装メモ
 ** Fragment内で実装している

==== 爆弾を踏んだらゲーム続行不可能にする

 * ボタンを押せなくします (@<code>{setEnabled()}, @<code>{isEnabled()})
 * ちなみに初期化時にまた押せるようにするのを忘れないように……

==== 爆弾をランダムに配置する

===== 参考: 最初のクリックでは爆弾を踏まないようにランダムに配置する

 * これが本来の挙動です。
 * 理屈は簡単: クリックした時に初期化する。

===== おまけ: 「ランダム」は実はとても難しい -> 乱数・擬似乱数の話、あるいはカルドセプトサーガ

==== 自動的に展開する

 * 本物と多分ちょっと違うが……
 * 爆弾が隣り合ってなかったら、隣もクリックしたことにしてしまう
 * 再帰呼び出し

==== 全部開いたら「クリアしました！」と表示して動作を止める

 * Resetがあるのでゲームの再開は簡単です

=== 今後の課題: 更にゲームを強化する

 * あくまで入り口だけを紹介
 ** あまりの速度でめまいがしたとしたら、すみません
 * これでは「売り物」にはしづらいかも？
 ** 昔はこれでも売れた

==== 「爆」ではなく爆弾アイコンを表示する

==== 8x8の固定画面から変更できるようにするには。あるいは「数字決め打ちがどれだけ害悪か」

 * これまでの方法だと'''非常にヨロシクない'''ことが分かる
 * 「8」という数字を各所で使いすぎている
 ** 増やすにも……
 * 変数を上手く活用しましょう！

==== 「旗」を立てたい

 * マウスと違って「右クリック」がない
 * 長押し？
 ** 最近あまり使われなくなっているらしい

==== 色々な端末に最適な見た目にするには

 * 骨がおれます。
 * 今回のようにレイアウトを固定にしては「いけません」
 ** サイズに併せてレイアウトを複数用意します。

==== 画面のローテーションに対応するには

 * Androidの奥深い世界へようこそ
 * 回転する際に画面を一旦破棄します
 * おおまかにやるべきこと
 ** 状態を覚えておく
 ** 回転が終わった後に状態を復帰する
 * 今回は省略します

==== バグ……バグ……

 * 全体的に今回の実装はかなり手を抜いています
 * 古いデバイスで多分動かない？
 * Android開発は始まったばかりです

== 今回取り上げなかったこと。本来の開発で起こること

 * 3Dゲームは別の機構が必要 (Unity使うのもありだね)
 * この方法でノベルゲームを作るのは可能、かも、しれないが……
 ** 無理な例: White Album (初代, PS3版)
 *** 地味に3Dレンダリングを多用している
 * 本当のゲーム制作では「仕様」から吟味する必要がある
 ** どのくらいの爆弾数が面白いだろうか……？
 ** "Mine Sweeper" って罰当たりよな！？
 ** 「新しい」ことをやる場合はこのあたりでけっつまづく
 * 多機種対応や色々な画面遷移があるとあっという間に複雑になる
 * UIの作りこみも時間がかかる
 ** 「旗」や「両ボタンクリック」のないマインスイーパーは快適とは程遠い。
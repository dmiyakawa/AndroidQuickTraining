package com.example.training;

import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;

public class MainActivityDay2_3_GameOverSupported extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (savedInstanceState == null) {
            getSupportFragmentManager().beginTransaction()
                    .add(R.id.container, new PlaceholderFragment()).commit();
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {

        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    /**
     * A placeholder fragment containing a simple view.
     */
    public static class PlaceholderFragment extends Fragment implements OnClickListener {
        private int[][] mButtonIds = new int[8][8];
        private int[][] mButtonStates = new int[8][8];
        private boolean[][] mIsBomb = new boolean[8][8];
        
        public PlaceholderFragment() {
        }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                Bundle savedInstanceState) {            
            LinearLayout rootView = (LinearLayout)
                    inflater.inflate(R.layout.mine_fragment_day2,
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
            
            // ゲームを初期化します。
            initializeGameState(rootView);

            Button resetButton = (Button) rootView.findViewById(R.id.reset_button);
            resetButton.setOnClickListener(this);
            return rootView;
        }

        @Override
        public void onClick(View v) {
            View rootView = getView();
            if (v.getId() == R.id.reset_button) {
                initializeGameState(rootView);
                return;
            }

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
                Log.d("test", "KA-BOOM!! x=" + view_x + ", y=" + view_y);
                ((Button) v).setText("爆");
                ((Button) v).setTextColor(Color.RED);

                // 全てのボタンを押せなくします
                for (int x = 0; x < 8; x++) {
                    for (int y = 0; y < 8; y++) {
                        Button button = (Button)rootView.findViewById(mButtonIds[x][y]);
                        button.setEnabled(false);
                    }
                }
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
                Button button = (Button) v;
                button.setText(String.valueOf(numOfBombs));
            }
        }

        // 初期化する
        private void initializeGameState(View rootView) {
            // ボタンに対応するidを覚えます
            setupButtonIds();
            
            // ボタンの状態をリセットします
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    // ボタンに触れてない
                    mButtonStates[x][y] = 0;
                    
                    // 書き込んだ文字を消します
                    Button button = (Button)rootView.findViewById(mButtonIds[x][y]);
                    button.setText("");
                    button.setEnabled(true);
                }
            }
            
            // 爆弾を配置します。まず初期化
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    // ボタンに触れてない
                    mIsBomb[x][y] = false;
                }
            }
            // 左上 (座標 0,0) に爆弾が一つ
            mIsBomb[0][0] = true;
            // 座標 3, 4 に爆弾が一つ = 左から「4」つめ、上から「5」つめ (いわゆる「0-origin」)
            mIsBomb[3][4] = true;
            mIsBomb[5][6] = true;
            mIsBomb[6][2] = true;
        }
        
        private void setupButtonIds() {
            // mButtonIds 配列に既存のレイアウトのidを入れていきます。
            //
            // 本格的な実装ではこういうことはあまりしません :-)
            // より良い方法 (いくつもありますが、その中から)
            // 1. View#generateViewId() を使う
            // 2. setTag() と findViewWithTag() を使う
            mButtonIds[0][0] = R.id.button00;
            mButtonIds[0][1] = R.id.button01;
            mButtonIds[0][2] = R.id.button02;
            mButtonIds[0][3] = R.id.button03;
            mButtonIds[0][4] = R.id.button04;
            mButtonIds[0][5] = R.id.button05;
            mButtonIds[0][6] = R.id.button06;
            mButtonIds[0][7] = R.id.button07;

            mButtonIds[1][0] = R.id.button10;
            mButtonIds[1][1] = R.id.button11;
            mButtonIds[1][2] = R.id.button12;
            mButtonIds[1][3] = R.id.button13;
            mButtonIds[1][4] = R.id.button14;
            mButtonIds[1][5] = R.id.button15;
            mButtonIds[1][6] = R.id.button16;
            mButtonIds[1][7] = R.id.button17;

            mButtonIds[2][0] = R.id.button20;
            mButtonIds[2][1] = R.id.button21;
            mButtonIds[2][2] = R.id.button22;
            mButtonIds[2][3] = R.id.button23;
            mButtonIds[2][4] = R.id.button24;
            mButtonIds[2][5] = R.id.button25;
            mButtonIds[2][6] = R.id.button26;
            mButtonIds[2][7] = R.id.button27;

            mButtonIds[3][0] = R.id.button30;
            mButtonIds[3][1] = R.id.button31;
            mButtonIds[3][2] = R.id.button32;
            mButtonIds[3][3] = R.id.button33;
            mButtonIds[3][4] = R.id.button34;
            mButtonIds[3][5] = R.id.button35;
            mButtonIds[3][6] = R.id.button36;
            mButtonIds[3][7] = R.id.button37;

            mButtonIds[4][0] = R.id.button40;
            mButtonIds[4][1] = R.id.button41;
            mButtonIds[4][2] = R.id.button42;
            mButtonIds[4][3] = R.id.button43;
            mButtonIds[4][4] = R.id.button44;
            mButtonIds[4][5] = R.id.button45;
            mButtonIds[4][6] = R.id.button46;
            mButtonIds[4][7] = R.id.button47;

            mButtonIds[5][0] = R.id.button50;
            mButtonIds[5][1] = R.id.button51;
            mButtonIds[5][2] = R.id.button52;
            mButtonIds[5][3] = R.id.button53;
            mButtonIds[5][4] = R.id.button54;
            mButtonIds[5][5] = R.id.button55;
            mButtonIds[5][6] = R.id.button56;
            mButtonIds[5][7] = R.id.button57;

            mButtonIds[6][0] = R.id.button60;
            mButtonIds[6][1] = R.id.button61;
            mButtonIds[6][2] = R.id.button62;
            mButtonIds[6][3] = R.id.button63;
            mButtonIds[6][4] = R.id.button64;
            mButtonIds[6][5] = R.id.button65;
            mButtonIds[6][6] = R.id.button66;
            mButtonIds[6][7] = R.id.button67;

            mButtonIds[7][0] = R.id.button70;
            mButtonIds[7][1] = R.id.button71;
            mButtonIds[7][2] = R.id.button72;
            mButtonIds[7][3] = R.id.button73;
            mButtonIds[7][4] = R.id.button74;
            mButtonIds[7][5] = R.id.button75;
            mButtonIds[7][6] = R.id.button76;
            mButtonIds[7][7] = R.id.button77;
        }
    }
}

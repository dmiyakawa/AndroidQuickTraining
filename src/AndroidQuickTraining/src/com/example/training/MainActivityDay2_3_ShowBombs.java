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

public class MainActivityDay2_3_ShowBombs extends ActionBarActivity {

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
        private boolean[][] mIsBomb = new boolean[8][8];

        public PlaceholderFragment() {
        }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                Bundle savedInstanceState) {
            mIsBomb[0][0] = true;
            mIsBomb[3][4] = true;
            mIsBomb[5][6] = true;
            mIsBomb[6][2] = true;
            
            LinearLayout rootView = (LinearLayout)
                    inflater.inflate(R.layout.mine_fragment_day2, container, false);
            for (int index=0, y=0; index < rootView.getChildCount(); index++) {
                View child = rootView.getChildAt(index);
                if (child instanceof LinearLayout) {
                    LinearLayout childAsLinearLayout = (LinearLayout) child;
                    for (int index2=0, x=0; index2 < childAsLinearLayout.getChildCount(); index2++) {
                        View grandchild = childAsLinearLayout.getChildAt(index2);
                        if (grandchild instanceof Button) {
                            ((Button) grandchild).setOnClickListener(this);
                            mButtonIds[x][y] = grandchild.getId();
                            x++;
                        }
                    }
                    y++;
                }
            }
            return rootView;
        }

        @Override
        public void onClick(View v) {
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
            if (mIsBomb[view_x][view_y]) {
                ((Button) v).setText("爆");
                ((Button) v).setTextColor(Color.RED);
            } else {
                ((Button) v).setText("開");
            }
        }
    }
}

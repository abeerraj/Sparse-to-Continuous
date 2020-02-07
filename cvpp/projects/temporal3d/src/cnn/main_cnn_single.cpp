
#include "aux_cnn.h"
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/objects/object_camera.h>

using namespace cvpp;

int main( int argc , char* argv[] )
{
    int n = 0;

//    String path = "/media/vguizilini/ETERNIA/Datasets/kitti/raw_data";
//    String type = "residential";
//    String date = "2011_09_26";
//    String fldr = "drive_0019_sync";

    String path = argv[1];
    String type = argv[2];
    String date = argv[3];
    String fldr = argv[4];

    String suf = type + "_" + date + "_" + fldr + "_";
    String dir_data = path + "/data/" + type + "/" + date + "_" + fldr + "/";
    String dir_calib = path + "/calib_files/" + date + "/";

    Seq<String> str_img = get_files( dir_data + "image_02/data/" , n );
    Seq<String> str_vel = get_files( dir_data + "velodyne_points/data/" , n );
    Seq<String> str_gps = get_files( dir_data + "oxts/data/" , n );

    n = str_img.size();

    prep_dirs( dir_data );

    SeqMatd vels = load_vel( str_vel );
    Seq<Img3c> imgs = load_img( str_img );
    Seq<Posef> poses = load_pos( str_gps );

    int r = imgs[0].r() , c = imgs[0].c();

//    CPPlot draw( "Window" , ULHW( 2 * r , c ) , 2 , 1 );
//    draw[0].set3Dworld();
//    draw[1].set2Dimage().setResolution( imgs[0] );

//    glPixelStorei( GL_UNPACK_ALIGNMENT , 1 );

    Matf K, D, R, P;
    load_cam2cam( dir_calib , K , D , R , P );
    Matf T = load_vel2cam( dir_calib );

    Matf G = load_imu2vel( dir_calib );
    Posef gps; gps.setPose( G );
    forLOOPi( poses.size() ) poses[i] -= gps;

    Matf iP = MatIDTYf( 4 );
    iP.cl(3) = P.clone(); iP = iP.inv();
    Matf iR = R.t() , iT = T.inv();

    Matf TRP = T * R * P;
    Matf iPRT = iP * iR * iT;

    Matf vel,xyz,proj,uv,dep;
//    int tex_img,tex_dsp,buf_vel,buf_xyz,buf_clr,buf_uv,buf_dep;

    int t = 0 , tm = imgs.size();
    bool change = true;

    Img1f dspf( imgs[t].dims() );
    Img1c dspc;

//    tex_img = draw.addTexture3U( imgs[0] );
//    tex_dsp = draw.addTexture3U( imgs[0] );

//    buf_vel = draw.addBuffer3Df( 500000 );
//    buf_xyz = draw.addBuffer3Df( 200000 );
//    buf_clr = draw.addBuffer3Df( 200000 );
//    buf_uv  = draw.addBuffer2Df( 200000 );
//    buf_dep = draw.addBuffer3Df( 200000 );

    int show = 0;

    while( t < tm )
//    while( draw.input() )
    {
//        if( draw.keys.enter ) { show = ++show % 2; halt(100); }

//        if( draw.keys.up   ) { if( t < tm - 1 ) t++; change = true; }
//        if( draw.keys.down ) { if( t >      0 ) t--; change = true; }

        if( change )
        {
            process_frame( poses , vels , t , TRP , iPRT , r , c ,
                           vel , xyz , proj , uv , dep );

            create_images( uv , dep , dspf , dspc );

//            draw.updTexture( tex_img , imgs[t] );
//            draw.updTexture( tex_dsp , dspc );

//            draw.updBuffer3D( buf_vel , vel );
//            draw.updBuffer3D( buf_xyz , xyz );
//            draw.updBuffer3D( buf_clr , color_pts( uv , imgs[t] ) );
//            draw.updBuffer2D( buf_uv , uv );
//            draw.updBufferRGBjet( buf_dep , dep );

            save_data( suf , dir_data , str_img[t] , imgs[t] ,
                       dspf , dspc , vel , xyz , uv , dep );

            change = false;
//            halt(10);
        }

//        draw[0].clear();
//        draw.psc(1,WHI).pts3D( buf_vel );
//        draw.ps(4).pts3D( buf_xyz , buf_clr );

//        forLOOPi( poses.size() )
//            draw.psc(3,BLU).pt3D( poses[i].getPosPt() );
//        draw.psc(5,RED).pt3D( poses[t].getPosPt() );

//        draw[1].clear();

//        switch( show )
//        {
//            case 0:
//                draw.useTexture( tex_img );
//                draw.ps(2).pts2D( buf_uv , buf_dep ); break;
//            case 1:
//                draw.useTexture( tex_dsp ); break;
//        }

        if( t == tm - 1 ) break;
        t++; change = true; //disp(t);

//        draw.updateWindow(0);
    }


    return 0;
}

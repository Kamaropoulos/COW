//--------------------------------------------
// HONEY PROGRAMMING LANGUAGE
// by: Kamaropoulos kamaropoulos@outlook.com
//
// A Fork of the COW PROGRAMMING LANGUAGE
//           https://github.com/BigZaphod/COW
// by: BigZaphod sean@fifthace.com
// http://www.bigzaphod.org/cow/
// 
// License: Public Domain
//--------------------------------------------
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>

#define COMPILER    "g++"
#define FLAGS       "-O3 -x c++"
#define NAME_FLAG   "-o "
#define OUTPUT_EXEC "honey.out"
#define OUTPUT_CPP  "honey.out.cpp"


//#define PRETTY(s) fprintf( output, "\t\t\t// %s\n", s );
#define PRETTY(s)


typedef std::vector<int> mem_t;
mem_t program;
mem_t::iterator prog_pos;
FILE* output;

int yumcount(0);
int YUMcount(0);


void quit()
{
    printf( "Compile error.  Invalid source code.\n" );
    exit(1);
}

bool compile( int instruction, bool advance )
{
    switch( instruction )
    {
        // moo
        case 0:
        {
            int level = 1;
            int num = YUMcount + 1;
            mem_t::iterator t = prog_pos;

            t--;   // skip past previous command when searching for MOO.
            if( t != program.begin() )
            {
                if((*t) == 7 )
                    num--;

                while( level > 0 )
                {
                    if( t == program.begin() )
                        break;

                    t--;

                    if( (*t) == 0 )
                        level++;
                    else
                    if( (*t) == 7 )  // look for MOO
                    {
                        level--;
                        num--;
                    }
                }
            }
            if( level != 0 && advance )
                quit();
            else if( level != 0 )
            {
                fprintf( output, "rterr();" );
                break;
            }

            yumcount++;
            fprintf( output, "goto H%d;", num );
            fprintf( output, "h%d:", yumcount );
            PRETTY( "moo" );
        }
            break;


            // yUm
        case 1:
            fprintf( output, "if(p==m.begin()){rterr();}else{p--;}" );
            PRETTY( "yUm" );
            break;

            // yuM
        case 2:
            fprintf( output, "p++; if(p==m.end()){m.push_back(0);p=m.end();p--;}" );
            PRETTY( "yuM" );
            break;

            // yUM
        case 3:
            fprintf( output, "switch(*p){" );
            fprintf( output, "case 0:{" ); compile( 0, false ); fprintf( output, "}break;" );
            fprintf( output, "case 1:{" ); compile( 1, false ); fprintf( output, "}break;" );
            fprintf( output, "case 2:{" ); compile( 2, false ); fprintf( output, "}break;" );
            fprintf( output, "case 4:{" ); compile( 4, false ); fprintf( output, "}break;" );
            fprintf( output, "case 5:{" ); compile( 5, false ); fprintf( output, "}break;" );
            fprintf( output, "case 6:{" ); compile( 6, false ); fprintf( output, "}break;" );
            fprintf( output, "case 7:{" ); compile( 7, false ); fprintf( output, "}break;" );
            fprintf( output, "case 8:{" ); compile( 8, false ); fprintf( output, "}break;" );
            fprintf( output, "case 9:{" ); compile( 9, false ); fprintf( output, "}break;" );
            fprintf( output, "case 10:{" ); compile( 10, false ); fprintf( output, "}break;" );
            fprintf( output, "case 11:{" ); compile( 11, false ); fprintf( output, "}break;" );
            fprintf( output, "default:{goto x;}};" );
            PRETTY( "yUM" );
            break;

            // Yum
        case 4:
            fprintf( output, "if((*p)!=0){putchar(*p);}else{(*p)=getchar();while(getchar()!='\\n');}" );
            PRETTY( "Yum" );
            break;

            // YUm
        case 5:
            fprintf( output, "(*p)--;" );
            PRETTY( "YUm" );
            break;

            // MoO
        case 6:
            fprintf( output, "(*p)++;" );
            PRETTY( "YuM" );
            break;

            // YUM
        case 7:
        {
            int level = 1;
            int num = yumcount;
            int prev = 0;
            mem_t::iterator t = prog_pos;
            t++;      // have to skip past next command when looking for next yum.

            if( t != program.end() )
            {
                if( (*t) == 0 )
                    num++;

                while( level > 0 )
                {
                    prev = *t;
                    t++;

                    if( t == program.end() )
                        break;

                    if( (*t) == 7 ) // look for YUM command.
                        level++;
                    else
                    if( (*t) == 0 ) // look for yum command.
                    {
                        if( prev == 7 )
                            level--;

                        level--;
                        num++;
                    }

                    if( level == 0 )
                        break;
                }
            }
            if( advance && level != 0 )
                quit();
            else if( level != 0 )
            {
                fprintf( output, "rterr();" );
                break;
            }

            YUMcount++;
            fprintf( output, "H%d:", YUMcount );
            fprintf( output, "if(!(*p))goto h%d;", num );
            PRETTY( "YUM" );
        }
            break;

            // UUU
        case 8:
            fprintf( output, "(*p)=0;" );
            PRETTY( "UUU" );
            break;

            // MMM
        case 9:
            fprintf( output, "if(h){(*p)=r;}else{r=(*p);}h=!h;" );
            PRETTY( "MMM" );
            break;

            // MUY
        case 10:
            fprintf( output, "printf(\"%%d\\n\",*p);" );
            PRETTY( "MUY" );
            break;

            // yum
        case 11:
            fprintf( output, "char b[100];int c=0;" );
            fprintf( output, "while(c<sizeof(b)-1){b[c]=getchar();c++;b[c]=0;if(b[c-1]=='\\n')break;}" );
            fprintf( output, "if(c==sizeof(b))while(getchar()!='\\n');(*p)=atoi(b);" );
            PRETTY( "yum" );
            break;

            // bad stuff
        default:
            return false;
    };

    if( advance )
        prog_pos++;

    return true;
}


int main( int argc, char** argv )
{
    if( argc < 2 )
    {
        printf( "Usage: %s program.honey\n\n", argv[0] );
        exit( 1 );
    }

    FILE* f = fopen( argv[1], "rb" );

    if( f == NULL )
    {
        printf( "Cannot open source file [%s].\n", argv[1] );
        exit( 1 );
    }

    char buf[3];
    memset( buf, 0, 3 );
    int pos = 0;

    while( !feof(f) )
    {
        int found = 0;
        buf[2] = fgetc( f );

        if( found = !strncmp( "yum", buf, 3 ) )
            program.push_back( 0 );
        else if( found = !strncmp( "yUm", buf, 3 ) )
            program.push_back( 1 );
        else if( found = !strncmp( "yuM", buf, 3 ) )
            program.push_back( 2 );
        else if( found = !strncmp( "yUM", buf, 3 ) )
            program.push_back( 3 );
        else if( found = !strncmp( "Yum", buf, 3 ) )
            program.push_back( 4 );
        else if( found = !strncmp( "YUm", buf, 3 ) )
            program.push_back( 5 );
        else if( found = !strncmp( "YuM", buf, 3 ) )
            program.push_back( 6 );
        else if( found = !strncmp( "YUM", buf, 3 ) )
            program.push_back( 7 );
        else if( found = !strncmp( "UUU", buf, 3 ) )
            program.push_back( 8 );
        else if( found = !strncmp( "MMM", buf, 3 ) )
            program.push_back( 9 );
        else if( found = !strncmp( "MUY", buf, 3 ) )
            program.push_back( 10 );
        else if( found = !strncmp( "MUY", buf, 3 ) )
            program.push_back( 11 );

        if( found )
        {
            memset( buf, 0, 3 );
        }
        else
        {
            buf[0] = buf[1];
            buf[1] = buf[2];
            buf[2] = 0;
        }
    }

    fclose( f );

    printf( "Compiling [%s]...\n", argv[1] );

    // init main memory.
    /*
    memory.push_back( 0 );
    mem_pos = memory.begin();
    */

    output = fopen( "honey.out.cpp", "wb" );
    fprintf( output, "#include <stdio.h>\n" );
    fprintf( output, "#include <vector>\n" );
    fprintf( output, "typedef std::vector<int> t_;t_ m;t_::iterator p;\n" );
    fprintf( output, "bool h;int r;\n" );
    fprintf( output, "void rterr(){puts(\"Runtime error.\\n\");}\n" );
    fprintf( output, "int main(int a,char** v){\n" );
    fprintf( output, "m.push_back(0);p=m.begin();h=false;\n" );

    prog_pos = program.begin();
    while( prog_pos != program.end() )
        if( !compile( *prog_pos, true ) )
        {
            printf( "ERROR!\n" );
            break;
        }

    fprintf( output, "x:return(0);}\n" );
    fclose( output );

    printf( "C++ source code: honey.out.cpp\n" );

#ifdef COMPILER
    std::string path( (const char*)COMPILER );
    path.append( " " );
    path.append( (const char*)NAME_FLAG );
    path.append( " " );
    path.append( (const char*)OUTPUT_EXEC );
    path.append( " " );
    path.append( (const char*)FLAGS );
    path.append( " " );
    path.append( (const char*)OUTPUT_CPP );
    if( system( path.c_str() ) )
        printf( "\n\nCould not compile.  Possible causes:  C++ compiler is not installed, not in path, or not named '%s' or there is a bug in this compiler.\n\n", COMPILER );
    else
        printf( "Executable created: honey.out\n" );
#endif

    return 0;
}

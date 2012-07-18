
VariantDir('build', 'src', duplicate=0)
VariantDir('build/test', 'test', duplicate=0)
VariantDir('build/gtest', 'gtest/src', duplicate=0)

env = Environment(CCFLAGS = '-Wall -std=c++0x -O2')
env.Program('rftgscore', source = Glob('build/*.cc'))


test_env = env.Clone()

# Compile gtest
test_env.Library('lib/gtest_main',
                 source = Glob('build/gtest/*.cc'),
                 CPPPATH = ['gtest/include/', 'gtest/'])                
                 
# We don't want to link with main.o since we want the main() in gtest_main                 
test_sources = filter(lambda x: x.rstr() != 'build/main.o',
                      Glob('build/test/*.cc') + Glob('build/*.o'))


test_env.Program('test_rftgscore',
                 source = test_sources,
                 LIBS = ['gtest_main'],
                 LIBPATH = 'lib/',
                 LINKFLAGS = '-pthread',
                 CPPPATH = ['gtest/include/','src/'])

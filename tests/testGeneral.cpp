//
// Created by Alexander on 27.03.2025.
//



#include "testGeneral.h"



namespace testConstants
{
    const unsigned int precision{6};

    const unsigned int maxResponses{5};
}


const std::string& ProgramArguments::configFilePath()
    {
        //Значение по умолчанию
        static const std::string variable{"../../tests/resources/config-test.json"};
        return variable;
    }

const std::string& ProgramArguments::configFilePath_2()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/config-test-2.json"};
    return variable;
}

const std::string& ProgramArguments::configFilePath_missing()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/config-test-missing.json"};
    return variable;
}

const std::string& ProgramArguments::configFilePath_filesEmpty()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/config-test-files-empty.json"};
    return variable;
}

const std::string& ProgramArguments::configFilePath_file003_missing()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/config-test-file003-missing.json"};
    return variable;
}

const std::string& ProgramArguments::requestsFilePath()
    {
        //Значение по умолчанию
        static const std::string variable{"../../tests/resources/requests-test.json"};
        return variable;
    }

const std::string& ProgramArguments::requestsFilePath_missing()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/requests-test-missing.json"};
    return variable;
}

const std::string& ProgramArguments::requestsFilePath_requestsEmpty()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/requests-test-requests-empty.json"};
    return variable;
}

const std::string& ProgramArguments::answersFilePath()
    {
        //Значение по умолчанию
        static const std::string variable{"../../tests/resources/answers-test.json"};
        return variable;
    }

const std::string& ProgramArguments::readJSONFile()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/readJSONFile.json"};
    return variable;
}

const std::string& ProgramArguments::readTextFile()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/readTextFile.txt"};
    return variable;
}

const std::string& ProgramArguments::checkRequestsArray()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/checkRequestsArray.json"};
    return variable;
}

const std::string& ProgramArguments::answersFilePath_empty()
{
    //Значение по умолчанию
    static const std::string variable;
    return variable;
}

const std::string& ProgramArguments::documentsBaseOrPathsBase()
    {
        //Значение по умолчанию
        static const std::string variable{Constants::default_documentsBaseOrPathsBase()};
        return variable;
    }

const std::string& ProgramArguments::documentsBaseOrPathsBase_no()
{
    //Значение по умолчанию
    static const std::string variable{Constants::documentsBaseOrPathsBase_no()};
    return variable;
}

const std::string& ProgramArguments::configLoggerFilePath()
    {
        //Значение по умолчанию
        static const std::string variable{"../../tests/resources/logger.json"};
        return variable;
    }

const std::string& ProgramArguments::configWriterMessageFilePath()
    {
        //Значение по умолчанию
        static const std::string variable{"../../tests/resources/messageQueue.json"};
        return variable;
    }

const std::string& ProgramArguments::logsFolderName()
{
    //Значение по умолчанию
    static const std::string variable{"Logs"};
    return variable;
}

const std::string& ProgramArguments::jsonFileName()
{
    //Значение по умолчанию
    static const std::string variable{"writeJSONFile.json"};
    return variable;
}

const std::string& ProgramArguments::dispatcherOperations_writeJSONFile_info()
{
    //Значение по умолчанию
    static const std::string variable{"DispatcherOperations_writeJSONFile_info"};
    return variable;
}

const std::string& ProgramArguments::errorLevel_debug()
{
    //Значение по умолчанию
    static const std::string variable{"DEBUG"};
    return variable;
}

const std::string& ProgramArguments::errorLevel_info()
{
    //Значение по умолчанию
    static const std::string variable{"INFO"};
    return variable;
}

const std::string& ProgramArguments::errorLevel_warn()
{
    //Значение по умолчанию
    static const std::string variable{"WARNING"};
    return variable;
}

const std::string& ProgramArguments::errorLevel_error()
{
    //Значение по умолчанию
    static const std::string variable{"ERROR"};
    return variable;
}

const std::string& ProgramArguments::errorLevel_fatal()
{
    //Значение по умолчанию
    static const std::string variable{"FATAL"};
    return variable;
}

const std::string& ProgramArguments::dateTimeFormat()
{
    //Значение по умолчанию
    static const std::string variable{"%Y-%m-%d %H:%M:%S."};
    return variable;
}

const std::string& ProgramArguments::launchConsole_yes()
    {
        //Значение по умолчанию
        static const std::string variable{"yes"};
        return variable;
    }

const std::string& ProgramArguments::launchConsole_no()
{
    //Значение по умолчанию
    static const std::string variable{"no"};
    return variable;
}

const unsigned int& ProgramArguments::precision()
    {
        //Значение по умолчанию
        static const unsigned int variable{6};
        return variable;
    }

const unsigned int& ProgramArguments::precision_3()
{
    //Значение по умолчанию
    static const unsigned int variable{3};
    return variable;
}

const int& ProgramArguments::formatByWidth()
    {
        //Значение по умолчанию
        static const int variable{2};
        return variable;
    }

unsigned int ProgramArguments::desiredNumberOfThreads()
    {
        //Значение по умолчанию
        static const unsigned int variable{std::thread::hardware_concurrency() - 1};
        return variable;
    }

unsigned int ProgramArguments::desiredNumberOfThreads_3()
{
    //Значение по умолчанию
    static const unsigned int variable{3};
    return variable;
}

const std::size_t& ProgramArguments::maximumAllowableErrorsNumber()
    {
        //Значение по умолчанию
        static const std::size_t variable{0};
        return variable;
    }

const std::size_t& ProgramArguments::maximumAllowableErrorsNumber_1()
{
    //Значение по умолчанию
    static const std::size_t variable{1};
    return variable;
}

unsigned int ProgramArguments::maxResponses()
{
    //Значение по умолчанию
    static const unsigned int variable{5};
    return variable;
}



const std::vector<std::string> &Bases::documents()
    {
        static const std::vector<std::string> varDocuments
                {
                     "modern american movies of the past    years have introduced to the audiences a fresh generation of actors  kevin spacey  russell crowe  brad pitt  john cusack  matt damon  edward norton  frances mcdormand  gwyneth paltrow and julianne moore have given performances as vivid as their illustrious predecessors  unlike the iconic stars of hollywood s classic era  who always seemed to be playing themselves   stars like cary grant  john wayne  gary cooper  clark gable  elizabeth taylor   the current generation of american actors disappear into their roles  playing parts that differ from one movie to the next  most of their movies are financed by hollywood  they are a promise to the variety of american filmmaking on important reason for this eclecticism is the impact of smaller  semi independent studios  studios like sony pictures classics and dream works specialize in producing or distributing avant garde movies   however  no studio head has been more influential or more successful in promoting innovative american  as well as foreign language films  than harvey weinstein of miramax  in many ways  weinstein is the crucial link between the movies of the     s and those of the past    years  when weinstein launched miramax in       he wanted to produce the sort of challenging films he had adored in his youth  this is precisely what he has done  miramax has been responsible for bringing to the united states foreign films like the crying game  cinema paradiso  ii postino  life is beautiful  and like water for chocolate  all of these films made money  despite the stereotype abroad that americans will only pay to see blockbuster movies made in hollywood   still  no matter how important the contributions and convictions of particular producers  directors or actors have been  what contemporary american movies have most in common with the films of the     s and     s  is a seriousness of artistic purpose combined with a desire to enthrall the audience  these twin ambitions are  by no means  uniquely american  wherever they have come from  the greatest directors   charlie chaplin  orson welles  alfred hitchcock  john ford  howard hawks  federico fellini  francis ford coppola  martin scorsese  steven spielberg   they have always recognized the intimate relationship between entertainment and art   to sum it up american films of the new generation are more open to their audience feelings  emotions  the inside world  thoughts and actions  people of the new american generation have a great opportunity to watch what is going on inside them in the movies shot outside ",
                     "off to the airport  don t forget the worms in a can and the beginner s guide to travelling by air  presented by dave barry  the officer at miami international airport  to help prevent unnecessary airport delays and strangling  consult the beginner s guide to travelling by air   when to be at the airport  you should be at the airport already   how much luggage can you carry on  you can carry one small bag and one medium bag  for a total of two bags  you may not carry on three bags by insisting to airport personnel that one of your bags is not really a bag  as if it is some kind of magical invisible fairy bag that airline personnel cannot see  you also may not carry on a suitcase the size of a sleeper sofa  apparently containing the entire wardrobe of some broadway production  the fact that your suitcase has wheels does not automatically mean that you may carry it on the airplane  a piano also has wheels  but you wouldn t try to take a piano onto a plane  would you   prohibited objects  you may not take knives  guns spears  armored personnel carrier  flame throwers  scary animals or sharp objects  if you know karate or kung fu  you may take your hands on board  but you must keep them clasped tightly under you armpits throughout the flight   how to go through the security check point  have your boarding pass and photo id ready  remove all your possessions from your pockets and put them in a plastic tray  have your boarding pass and photo id ready  remove your belt  shoes  and pacemakers and put them in another plastic tray  have your boarding pass and photo id ready  remove your laptop computer and put this in another plastic tray  for god s sake have your boarding pass and photo id ready  put everything   trays  bags  children under     on the moving belt  then stand in a non terroristic manner until the security person signals to you  at which time  while holding your boarding pass and photo id up  you should shuffle meekly forward until your pants fall to the floor   joking around with the security personnel  airport security personnel are a whacky and fun loving group who are bored to death from spending eight hours a day reminding morons to have their boarding passes and photo ids ready  there is nothing they enjoy more  than a good joke  such as the one where you give the victim a can that says   peanut brittle   when he opens it  giant spring loaded worms come shooting out  that always sets off a round of hearty knee slapping at the checkpoint   to crown it all  if you just use your common sense  waiting in long lines at the airport won t be tough on you ",
                     "america s music culture would be incomplete without blues music  thought it was created in the early decades of the   th century  blues music has had a huge influence on american popular music up to the present days  in fact  many key elements we hear in pop  soul  rhythm and blues  rock and roll  have their beginnings in blues music  it has never been the leader in music sales  blues music has retained a significant presence not only in concerts and festivals throughout the united states  but in the daily life of every person on the planet  as well  one can hear the sound of the blues in unexpected places  from a television commercial to a new country or western song   the best known blues musician today is b b  king  his fame is well deserved  born in indianola  mississippi in       he earned the nickname  b b     blues boy   while playing on radio programs in memphis  tennessee  from the     s through the     s  he played mostly in clubs in the south that had only black audiences  in       he had a hit record with  three a m  blues  and toured steadily thereafter  his fame spread as he played at blues festivals  concert halls  universities  and on television shows across the country  no other blues artist has worked harder  than b  b  king in his many years of playing over three hundred shows a year   by the late     s  b  b  had perfected his famous guitar style of vibrating the fingers of his left hand as he played  and bending notes to achieve the blues notes  that are such an integral part of blue music  this singing guitar sound  coupled with his expressive tenor voice  brought king great success in      with the recording of  the thrill is gone   the song broke through the limited sales of the blues market to achieve mainstream success and brought b b  a grammy award   b b s songs display a wide range of emotions  in addition to the sadness  so fundamental to blue music  he combines humor with a keen understanding of human nature in  everybody lies a little sometimes  and  how blue can you get    king s long and distinguished career includes many musical collaborations  young rock musicians  in particular  appreciate his contributions to their genre  in      b b  played guitar and sang on the hit song  when love comes to town  by the irish band u   in      he recorded an award winning record with eric clapton called  riding with the king     in a nutshell  king s guitar work has had a strong influence on thousands of guitar soloists to this day  b b  king remains the blues  greatest ambassador "
                };

        return varDocuments;
    }

const std::vector<std::string> &Bases::paths()
{
    static const std::vector<std::string> varDocuments
            {
                    "../../tests/resources/resources/file001-test.txt",
                    "../../tests/resources/resources/file002-test.txt",
                    "../../tests/resources/resources/file003-test.txt"
            };

    return varDocuments;
}

const std::vector<std::string> &Bases::paths_file003_missing()
{
    static const std::vector<std::string> varDocuments
            {
                    "../../tests/resources/resources/file001-test.txt",
                    "../../tests/resources/resources/file002-test.txt",
                    "../../tests/resources/resources/file003-test-missing.txt"
            };

    return varDocuments;
}

const std::map<std::string, std::vector<Entry>> &Bases::invertedIndex()
    {
        static const std::map<std::string, std::vector<Entry>> &varInvertedIndex
                {
                        {"a", {{0,5}, {1,15}, {2,13}}},
                        {"abroad", {{0,1}}},
                        {"achieve", {{2,2}}},
                        {"across", {{2,1}}},
                        {"actions", {{0,1}}},
                        {"actors", {{0,3}}},
                        {"addition", {{2,1}}},
                        {"adored", {{0,1}}},
                        {"air", {{1,2}}},
                        {"airline", {{1,1}}},
                        {"airplane", {{1,1}}},
                        {"airport", {{1,8}}},
                        {"alfred", {{0,1}}},
                        {"all", {{0,1}, {1,2}}},
                        {"already", {{1,1}}},
                        {"also", {{1,2}}},
                        {"always", {{0,2}, {1,1}}},
                        {"ambassador", {{2,1}}},
                        {"ambitions", {{0,1}}},
                        {"america", {{2,1}}},
                        {"american", {{0,8}, {2,1}}},
                        {"americans", {{0,1}}},
                        {"an", {{2,2}}},
                        {"and", {{0,8}, {1,14}, {2,10}}},
                        {"animals", {{1,1}}},
                        {"another", {{1,2}}},
                        {"apparently", {{1,1}}},
                        {"appreciate", {{2,1}}},
                        {"are", {{0,4}, {1,2}, {2,1}}},
                        {"armored", {{1,1}}},
                        {"armpits", {{1,1}}},
                        {"around", {{1,1}}},
                        {"art", {{0,1}}},
                        {"artist", {{2,1}}},
                        {"artistic", {{0,1}}},
                        {"as", {{0,4}, {1,2}, {2,3}}},
                        {"at", {{1,6}, {2,1}}},
                        {"audience", {{0,2}}},
                        {"audiences", {{0,1}, {2,1}}},
                        {"automatically", {{1,1}}},
                        {"avant", {{0,1}}},
                        {"award", {{2,2}}},
                        {"b", {{2,16}}},
                        {"bag", {{1,4}}},
                        {"bags", {{1,4}}},
                        {"band", {{2,1}}},
                        {"barry", {{1,1}}},
                        {"be", {{0,1}, {1,3}, {2,1}}},
                        {"beautiful", {{0,1}}},
                        {"been", {{0,3}, {2,1}}},
                        {"beginner", {{1,2}}},
                        {"beginnings", {{2,1}}},
                        {"belt", {{1,2}}},
                        {"bending", {{2,1}}},
                        {"best", {{2,1}}},
                        {"between", {{0,2}}},
                        {"black", {{2,1}}},
                        {"blockbuster", {{0,1}}},
                        {"blue", {{2,3}}},
                        {"blues", {{2,14}}},
                        {"board", {{1,1}}},
                        {"boarding", {{1,6}}},
                        {"bored", {{1,1}}},
                        {"born", {{2,1}}},
                        {"boy", {{2,1}}},
                        {"brad", {{0,1}}},
                        {"bringing", {{0,1}}},
                        {"brittle", {{1,1}}},
                        {"broadway", {{1,1}}},
                        {"broke", {{2,1}}},
                        {"brought", {{2,2}}},
                        {"but", {{1,2}, {2,1}}},
                        {"by", {{0,2}, {1,4}, {2,2}}},
                        {"called", {{2,1}}},
                        {"can", {{1,4}, {2,2}}},
                        {"cannot", {{1,1}}},
                        {"career", {{2,1}}},
                        {"carrier", {{1,1}}},
                        {"carry", {{1,5}}},
                        {"cary", {{0,1}}},
                        {"century", {{2,1}}},
                        {"challenging", {{0,1}}},
                        {"chaplin", {{0,1}}},
                        {"charlie", {{0,1}}},
                        {"check", {{1,1}}},
                        {"checkpoint", {{1,1}}},
                        {"children", {{1,1}}},
                        {"chocolate", {{0,1}}},
                        {"cinema", {{0,1}}},
                        {"clapton", {{2,1}}},
                        {"clark", {{0,1}}},
                        {"clasped", {{1,1}}},
                        {"classic", {{0,1}}},
                        {"classics", {{0,1}}},
                        {"clubs", {{2,1}}},
                        {"collaborations", {{2,1}}},
                        {"combined", {{0,1}}},
                        {"combines", {{2,1}}},
                        {"come", {{0,1}, {1,1}}},
                        {"comes", {{2,1}}},
                        {"commercial", {{2,1}}},
                        {"common", {{0,1}, {1,1}}},
                        {"computer", {{1,1}}},
                        {"concert", {{2,1}}},
                        {"concerts", {{2,1}}},
                        {"consult", {{1,1}}},
                        {"containing", {{1,1}}},
                        {"contemporary", {{0,1}}},
                        {"contributions", {{0,1}, {2,1}}},
                        {"convictions", {{0,1}}},
                        {"cooper", {{0,1}}},
                        {"coppola", {{0,1}}},
                        {"country", {{2,2}}},
                        {"coupled", {{2,1}}},
                        {"created", {{2,1}}},
                        {"crowe", {{0,1}}},
                        {"crown", {{1,1}}},
                        {"crucial", {{0,1}}},
                        {"crying", {{0,1}}},
                        {"culture", {{2,1}}},
                        {"current", {{0,1}}},
                        {"cusack", {{0,1}}},
                        {"daily", {{2,1}}},
                        {"damon", {{0,1}}},
                        {"dave", {{1,1}}},
                        {"day", {{1,1}, {2,1}}},
                        {"days", {{2,1}}},
                        {"death", {{1,1}}},
                        {"decades", {{2,1}}},
                        {"delays", {{1,1}}},
                        {"deserved", {{2,1}}},
                        {"desire", {{0,1}}},
                        {"despite", {{0,1}}},
                        {"differ", {{0,1}}},
                        {"directors", {{0,2}}},
                        {"disappear", {{0,1}}},
                        {"display", {{2,1}}},
                        {"distinguished", {{2,1}}},
                        {"distributing", {{0,1}}},
                        {"does", {{1,1}}},
                        {"don", {{1,1}}},
                        {"done", {{0,1}}},
                        {"dream", {{0,1}}},
                        {"early", {{2,1}}},
                        {"earned", {{2,1}}},
                        {"eclecticism", {{0,1}}},
                        {"edward", {{0,1}}},
                        {"eight", {{1,1}}},
                        {"elements", {{2,1}}},
                        {"elizabeth", {{0,1}}},
                        {"emotions", {{0,1}, {2,1}}},
                        {"enjoy", {{1,1}}},
                        {"entertainment", {{0,1}}},
                        {"enthrall", {{0,1}}},
                        {"entire", {{1,1}}},
                        {"era", {{0,1}}},
                        {"eric", {{2,1}}},
                        {"every", {{2,1}}},
                        {"everybody", {{2,1}}},
                        {"everything", {{1,1}}},
                        {"expressive", {{2,1}}},
                        {"fact", {{1,1}, {2,1}}},
                        {"fairy", {{1,1}}},
                        {"fall", {{1,1}}},
                        {"fame", {{2,2}}},
                        {"famous", {{2,1}}},
                        {"federico", {{0,1}}},
                        {"feelings", {{0,1}}},
                        {"fellini", {{0,1}}},
                        {"festivals", {{2,2}}},
                        {"filmmaking", {{0,1}}},
                        {"films", {{0,6}}},
                        {"financed", {{0,1}}},
                        {"fingers", {{2,1}}},
                        {"flame", {{1,1}}},
                        {"flight", {{1,1}}},
                        {"floor", {{1,1}}},
                        {"for", {{0,3}, {1,2}}},
                        {"ford", {{0,2}}},
                        {"foreign", {{0,2}}},
                        {"forget", {{1,1}}},
                        {"forward", {{1,1}}},
                        {"frances", {{0,1}}},
                        {"francis", {{0,1}}},
                        {"fresh", {{0,1}}},
                        {"from", {{0,2}, {1,2}, {2,2}}},
                        {"fu", {{1,1}}},
                        {"fun", {{1,1}}},
                        {"fundamental", {{2,1}}},
                        {"gable", {{0,1}}},
                        {"game", {{0,1}}},
                        {"garde", {{0,1}}},
                        {"gary", {{0,1}}},
                        {"generation", {{0,4}}},
                        {"genre", {{2,1}}},
                        {"get", {{2,1}}},
                        {"giant", {{1,1}}},
                        {"give", {{1,1}}},
                        {"given", {{0,1}}},
                        {"go", {{1,1}}},
                        {"god", {{1,1}}},
                        {"going", {{0,1}}},
                        {"gone", {{2,1}}},
                        {"good", {{1,1}}},
                        {"grammy", {{2,1}}},
                        {"grant", {{0,1}}},
                        {"great", {{0,1}, {2,1}}},
                        {"greatest", {{0,1}, {2,1}}},
                        {"group", {{1,1}}},
                        {"guide", {{1,2}}},
                        {"guitar", {{2,5}}},
                        {"guns", {{1,1}}},
                        {"gwyneth", {{0,1}}},
                        {"had", {{0,1}, {2,5}}},
                        {"halls", {{2,1}}},
                        {"hand", {{2,1}}},
                        {"hands", {{1,1}}},
                        {"harder", {{2,1}}},
                        {"harvey", {{0,1}}},
                        {"has", {{0,3}, {1,2}, {2,5}}},
                        {"have", {{0,7}, {1,5}, {2,1}}},
                        {"hawks", {{0,1}}},
                        {"he", {{0,3}, {1,1}, {2,7}}},
                        {"head", {{0,1}}},
                        {"hear", {{2,2}}},
                        {"hearty", {{1,1}}},
                        {"help", {{1,1}}},
                        {"his", {{0,1}, {2,7}}},
                        {"hit", {{2,2}}},
                        {"hitchcock", {{0,1}}},
                        {"holding", {{1,1}}},
                        {"hollywood", {{0,3}}},
                        {"hours", {{1,1}}},
                        {"how", {{0,1}, {1,2}, {2,1}}},
                        {"howard", {{0,1}}},
                        {"however", {{0,1}}},
                        {"huge", {{2,1}}},
                        {"human", {{2,1}}},
                        {"humor", {{2,1}}},
                        {"hundred", {{2,1}}},
                        {"iconic", {{0,1}}},
                        {"id", {{1,5}}},
                        {"ids", {{1,1}}},
                        {"if", {{1,3}}},
                        {"ii", {{0,1}}},
                        {"illustrious", {{0,1}}},
                        {"impact", {{0,1}}},
                        {"important", {{0,2}}},
                        {"in", {{0,8}, {1,6}, {2,22}}},
                        {"includes", {{2,1}}},
                        {"incomplete", {{2,1}}},
                        {"independent", {{0,1}}},
                        {"indianola", {{2,1}}},
                        {"influence", {{2,2}}},
                        {"influential", {{0,1}}},
                        {"innovative", {{0,1}}},
                        {"inside", {{0,2}}},
                        {"insisting", {{1,1}}},
                        {"integral", {{2,1}}},
                        {"international", {{1,1}}},
                        {"intimate", {{0,1}}},
                        {"into", {{0,1}}},
                        {"introduced", {{0,1}}},
                        {"invisible", {{1,1}}},
                        {"irish", {{2,1}}},
                        {"is", {{0,6}, {1,3}, {2,3}}},
                        {"it", {{0,1}, {1,4}, {2,2}}},
                        {"john", {{0,3}}},
                        {"joke", {{1,1}}},
                        {"joking", {{1,1}}},
                        {"julianne", {{0,1}}},
                        {"just", {{1,1}}},
                        {"karate", {{1,1}}},
                        {"keen", {{2,1}}},
                        {"keep", {{1,1}}},
                        {"kevin", {{0,1}}},
                        {"key", {{2,1}}},
                        {"kind", {{1,1}}},
                        {"king", {{2,7}}},
                        {"knee", {{1,1}}},
                        {"knives", {{1,1}}},
                        {"know", {{1,1}}},
                        {"known", {{2,1}}},
                        {"kung", {{1,1}}},
                        {"language", {{0,1}}},
                        {"laptop", {{1,1}}},
                        {"late", {{2,1}}},
                        {"launched", {{0,1}}},
                        {"leader", {{2,1}}},
                        {"left", {{2,1}}},
                        {"lies", {{2,1}}},
                        {"life", {{0,1}, {2,1}}},
                        {"like", {{0,4}}},
                        {"limited", {{2,1}}},
                        {"lines", {{1,1}}},
                        {"link", {{0,1}}},
                        {"little", {{2,1}}},
                        {"loaded", {{1,1}}},
                        {"long", {{1,1}, {2,1}}},
                        {"love", {{2,1}}},
                        {"loving", {{1,1}}},
                        {"luggage", {{1,1}}},
                        {"m", {{2,1}}},
                        {"made", {{0,2}}},
                        {"magical", {{1,1}}},
                        {"mainstream", {{2,1}}},
                        {"manner", {{1,1}}},
                        {"many", {{0,1}, {2,3}}},
                        {"market", {{2,1}}},
                        {"martin", {{0,1}}},
                        {"matt", {{0,1}}},
                        {"matter", {{0,1}}},
                        {"may", {{1,5}}},
                        {"mcdormand", {{0,1}}},
                        {"mean", {{1,1}}},
                        {"means", {{0,1}}},
                        {"medium", {{1,1}}},
                        {"meekly", {{1,1}}},
                        {"memphis", {{2,1}}},
                        {"miami", {{1,1}}},
                        {"miramax", {{0,3}}},
                        {"mississippi", {{2,1}}},
                        {"modern", {{0,1}}},
                        {"money", {{0,1}}},
                        {"moore", {{0,1}}},
                        {"more", {{0,3}, {1,1}}},
                        {"morons", {{1,1}}},
                        {"most", {{0,2}}},
                        {"mostly", {{2,1}}},
                        {"movie", {{0,1}}},
                        {"movies", {{0,7}}},
                        {"moving", {{1,1}}},
                        {"much", {{1,1}}},
                        {"music", {{2,9}}},
                        {"musical", {{2,1}}},
                        {"musician", {{2,1}}},
                        {"musicians", {{2,1}}},
                        {"must", {{1,1}}},
                        {"nature", {{2,1}}},
                        {"never", {{2,1}}},
                        {"new", {{0,2}, {2,1}}},
                        {"next", {{0,1}}},
                        {"nickname", {{2,1}}},
                        {"no", {{0,3}, {2,1}}},
                        {"non", {{1,1}}},
                        {"norton", {{0,1}}},
                        {"not", {{1,5}, {2,1}}},
                        {"notes", {{2,2}}},
                        {"nothing", {{1,1}}},
                        {"nutshell", {{2,1}}},
                        {"objects", {{1,2}}},
                        {"of", {{0,17}, {1,6}, {2,12}}},
                        {"off", {{1,2}}},
                        {"officer", {{1,1}}},
                        {"on", {{0,2}, {1,7}, {2,6}}},
                        {"one", {{0,1}, {1,4}, {2,1}}},
                        {"only", {{0,1}, {2,2}}},
                        {"onto", {{1,1}}},
                        {"open", {{0,1}}},
                        {"opens", {{1,1}}},
                        {"opportunity", {{0,1}}},
                        {"or", {{0,3}, {1,2}, {2,1}}},
                        {"orson", {{0,1}}},
                        {"other", {{2,1}}},
                        {"out", {{1,1}}},
                        {"outside", {{0,1}}},
                        {"over", {{2,1}}},
                        {"pacemakers", {{1,1}}},
                        {"paltrow", {{0,1}}},
                        {"pants", {{1,1}}},
                        {"paradiso", {{0,1}}},
                        {"part", {{2,1}}},
                        {"particular", {{0,1}, {2,1}}},
                        {"parts", {{0,1}}},
                        {"pass", {{1,5}}},
                        {"passes", {{1,1}}},
                        {"past", {{0,2}}},
                        {"pay", {{0,1}}},
                        {"peanut", {{1,1}}},
                        {"people", {{0,1}}},
                        {"perfected", {{2,1}}},
                        {"performances", {{0,1}}},
                        {"person", {{1,1}, {2,1}}},
                        {"personnel", {{1,5}}},
                        {"photo", {{1,6}}},
                        {"piano", {{1,2}}},
                        {"pictures", {{0,1}}},
                        {"pitt", {{0,1}}},
                        {"places", {{2,1}}},
                        {"plane", {{1,1}}},
                        {"planet", {{2,1}}},
                        {"plastic", {{1,3}}},
                        {"played", {{2,4}}},
                        {"playing", {{0,2}, {2,2}}},
                        {"pockets", {{1,1}}},
                        {"point", {{1,1}}},
                        {"pop", {{2,1}}},
                        {"popular", {{2,1}}},
                        {"possessions", {{1,1}}},
                        {"postino", {{0,1}}},
                        {"precisely", {{0,1}}},
                        {"predecessors", {{0,1}}},
                        {"presence", {{2,1}}},
                        {"present", {{2,1}}},
                        {"presented", {{1,1}}},
                        {"prevent", {{1,1}}},
                        {"produce", {{0,1}}},
                        {"producers", {{0,1}}},
                        {"producing", {{0,1}}},
                        {"production", {{1,1}}},
                        {"programs", {{2,1}}},
                        {"prohibited", {{1,1}}},
                        {"promise", {{0,1}}},
                        {"promoting", {{0,1}}},
                        {"purpose", {{0,1}}},
                        {"put", {{1,4}}},
                        {"radio", {{2,1}}},
                        {"range", {{2,1}}},
                        {"ready", {{1,5}}},
                        {"really", {{1,1}}},
                        {"reason", {{0,1}}},
                        {"recognized", {{0,1}}},
                        {"record", {{2,2}}},
                        {"recorded", {{2,1}}},
                        {"recording", {{2,1}}},
                        {"relationship", {{0,1}}},
                        {"remains", {{2,1}}},
                        {"reminding", {{1,1}}},
                        {"remove", {{1,3}}},
                        {"responsible", {{0,1}}},
                        {"retained", {{2,1}}},
                        {"rhythm", {{2,1}}},
                        {"riding", {{2,1}}},
                        {"rock", {{2,2}}},
                        {"roles", {{0,1}}},
                        {"roll", {{2,1}}},
                        {"round", {{1,1}}},
                        {"russell", {{0,1}}},
                        {"s", {{0,4}, {1,3}, {2,7}}},
                        {"sadness", {{2,1}}},
                        {"sake", {{1,1}}},
                        {"sales", {{2,2}}},
                        {"sang", {{2,1}}},
                        {"says", {{1,1}}},
                        {"scary", {{1,1}}},
                        {"scorsese", {{0,1}}},
                        {"security", {{1,4}}},
                        {"see", {{0,1}, {1,1}}},
                        {"seemed", {{0,1}}},
                        {"semi", {{0,1}}},
                        {"sense", {{1,1}}},
                        {"seriousness", {{0,1}}},
                        {"sets", {{1,1}}},
                        {"sharp", {{1,1}}},
                        {"shoes", {{1,1}}},
                        {"shooting", {{1,1}}},
                        {"shot", {{0,1}}},
                        {"should", {{1,2}}},
                        {"shows", {{2,2}}},
                        {"shuffle", {{1,1}}},
                        {"signals", {{1,1}}},
                        {"significant", {{2,1}}},
                        {"singing", {{2,1}}},
                        {"size", {{1,1}}},
                        {"slapping", {{1,1}}},
                        {"sleeper", {{1,1}}},
                        {"small", {{1,1}}},
                        {"smaller", {{0,1}}},
                        {"so", {{2,1}}},
                        {"sofa", {{1,1}}},
                        {"soloists", {{2,1}}},
                        {"some", {{1,2}}},
                        {"sometimes", {{2,1}}},
                        {"song", {{2,3}}},
                        {"songs", {{2,1}}},
                        {"sony", {{0,1}}},
                        {"sort", {{0,1}}},
                        {"soul", {{2,1}}},
                        {"sound", {{2,2}}},
                        {"south", {{2,1}}},
                        {"spacey", {{0,1}}},
                        {"spears", {{1,1}}},
                        {"specialize", {{0,1}}},
                        {"spending", {{1,1}}},
                        {"spielberg", {{0,1}}},
                        {"spread", {{2,1}}},
                        {"spring", {{1,1}}},
                        {"stand", {{1,1}}},
                        {"stars", {{0,2}}},
                        {"states", {{0,1}, {2,1}}},
                        {"steadily", {{2,1}}},
                        {"stereotype", {{0,1}}},
                        {"steven", {{0,1}}},
                        {"still", {{0,1}}},
                        {"strangling", {{1,1}}},
                        {"strong", {{2,1}}},
                        {"studio", {{0,1}}},
                        {"studios", {{0,2}}},
                        {"style", {{2,1}}},
                        {"success", {{2,2}}},
                        {"successful", {{0,1}}},
                        {"such", {{1,1}, {2,1}}},
                        {"suitcase", {{1,2}}},
                        {"sum", {{0,1}}},
                        {"t", {{1,3}}},
                        {"take", {{1,3}}},
                        {"taylor", {{0,1}}},
                        {"television", {{2,2}}},
                        {"tennessee", {{2,1}}},
                        {"tenor", {{2,1}}},
                        {"terroristic", {{1,1}}},
                        {"th", {{2,1}}},
                        {"than", {{0,1}, {1,1}, {2,1}}},
                        {"that", {{0,2}, {1,6}, {2,2}}},
                        {"the", {{0,25}, {1,21}, {2,28}}},
                        {"their", {{0,4}, {1,1}, {2,2}}},
                        {"them", {{0,1}, {1,3}}},
                        {"themselves", {{0,1}}},
                        {"then", {{1,1}}},
                        {"there", {{1,1}}},
                        {"thereafter", {{2,1}}},
                        {"these", {{0,2}}},
                        {"they", {{0,3}, {1,1}}},
                        {"this", {{0,2}, {1,1}, {2,2}}},
                        {"those", {{0,1}}},
                        {"thought", {{2,1}}},
                        {"thoughts", {{0,1}}},
                        {"thousands", {{2,1}}},
                        {"three", {{1,1}, {2,2}}},
                        {"thrill", {{2,1}}},
                        {"through", {{1,1}, {2,2}}},
                        {"throughout", {{1,1}, {2,1}}},
                        {"throwers", {{1,1}}},
                        {"tightly", {{1,1}}},
                        {"time", {{1,1}}},
                        {"to", {{0,11}, {1,13}, {2,9}}},
                        {"today", {{2,1}}},
                        {"total", {{1,1}}},
                        {"tough", {{1,1}}},
                        {"toured", {{2,1}}},
                        {"town", {{2,1}}},
                        {"travelling", {{1,2}}},
                        {"tray", {{1,3}}},
                        {"trays", {{1,1}}},
                        {"try", {{1,1}}},
                        {"twin", {{0,1}}},
                        {"two", {{1,1}}},
                        {"u", {{2,1}}},
                        {"under", {{1,2}}},
                        {"understanding", {{2,1}}},
                        {"unexpected", {{2,1}}},
                        {"uniquely", {{0,1}}},
                        {"united", {{0,1}, {2,1}}},
                        {"universities", {{2,1}}},
                        {"unlike", {{0,1}}},
                        {"unnecessary", {{1,1}}},
                        {"until", {{1,2}}},
                        {"up", {{0,1}, {1,1}, {2,1}}},
                        {"use", {{1,1}}},
                        {"variety", {{0,1}}},
                        {"vibrating", {{2,1}}},
                        {"victim", {{1,1}}},
                        {"vivid", {{0,1}}},
                        {"voice", {{2,1}}},
                        {"waiting", {{1,1}}},
                        {"wanted", {{0,1}}},
                        {"wardrobe", {{1,1}}},
                        {"was", {{2,1}}},
                        {"watch", {{0,1}}},
                        {"water", {{0,1}}},
                        {"wayne", {{0,1}}},
                        {"ways", {{0,1}}},
                        {"we", {{2,1}}},
                        {"weinstein", {{0,3}}},
                        {"well", {{0,1}, {2,2}}},
                        {"welles", {{0,1}}},
                        {"western", {{2,1}}},
                        {"whacky", {{1,1}}},
                        {"what", {{0,3}}},
                        {"wheels", {{1,2}}},
                        {"when", {{0,1}, {1,2}, {2,1}}},
                        {"where", {{1,1}}},
                        {"wherever", {{0,1}}},
                        {"which", {{1,1}}},
                        {"while", {{1,1}, {2,1}}},
                        {"who", {{0,1}, {1,1}}},
                        {"wide", {{2,1}}},
                        {"will", {{0,1}}},
                        {"winning", {{2,1}}},
                        {"with", {{0,2}, {1,1}, {2,6}}},
                        {"without", {{2,1}}},
                        {"won", {{1,1}}},
                        {"work", {{2,1}}},
                        {"worked", {{2,1}}},
                        {"works", {{0,1}}},
                        {"world", {{0,1}}},
                        {"worms", {{1,2}}},
                        {"would", {{1,1}, {2,1}}},
                        {"wouldn", {{1,1}}},
                        {"year", {{2,1}}},
                        {"years", {{0,2}, {2,1}}},
                        {"you", {{1,18}, {2,1}}},
                        {"young", {{2,1}}},
                        {"your", {{1,14}}},
                        {"youth", {{0,1}}}
                };

        return varInvertedIndex;
    }

const std::map<std::string, std::vector<Entry>> &Bases::invertedIndex_file003_missing()
{
    static const std::map<std::string, std::vector<Entry>> &varInvertedIndex
    {
            {"a", {{0,5}, {1,15}}},
            {"abroad", {{0,1}}},
            {"actions", {{0,1}}},
            {"actors", {{0,3}}},
            {"adored", {{0,1}}},
            {"air", {{1,2}}},
            {"airline", {{1,1}}},
            {"airplane", {{1,1}}},
            {"airport", {{1,8}}},
            {"alfred", {{0,1}}},
            {"all", {{0,1}, {1,2}}},
            {"already", {{1,1}}},
            {"also", {{1,2}}},
            {"always", {{0,2}, {1,1}}},
            {"ambitions", {{0,1}}},
            {"american", {{0,8}}},
            {"americans", {{0,1}}},
            {"and", {{0,8}, {1,14}}},
            {"animals", {{1,1}}},
            {"another", {{1,2}}},
            {"apparently", {{1,1}}},
            {"are", {{0,4}, {1,2}}},
            {"armored", {{1,1}}},
            {"armpits", {{1,1}}},
            {"around", {{1,1}}},
            {"art", {{0,1}}},
            {"artistic", {{0,1}}},
            {"as", {{0,4}, {1,2}}},
            {"at", {{1,6}}},
            {"audience", {{0,2}}},
            {"audiences", {{0,1}}},
            {"automatically", {{1,1}}},
            {"avant", {{0,1}}},
            {"bag", {{1,4}}},
            {"bags", {{1,4}}},
            {"barry", {{1,1}}},
            {"be", {{0,1}, {1,3}}},
            {"beautiful", {{0,1}}},
            {"been", {{0,3}}},
            {"beginner", {{1,2}}},
            {"belt", {{1,2}}},
            {"between", {{0,2}}},
            {"blockbuster", {{0,1}}},
            {"board", {{1,1}}},
            {"boarding", {{1,6}}},
            {"bored", {{1,1}}},
            {"brad", {{0,1}}},
            {"bringing", {{0,1}}},
            {"brittle", {{1,1}}},
            {"broadway", {{1,1}}},
            {"but", {{1,2}}},
            {"by", {{0,2}, {1,4}}},
            {"can", {{1,4}}},
            {"cannot", {{1,1}}},
            {"carrier", {{1,1}}},
            {"carry", {{1,5}}},
            {"cary", {{0,1}}},
            {"challenging", {{0,1}}},
            {"chaplin", {{0,1}}},
            {"charlie", {{0,1}}},
            {"check", {{1,1}}},
            {"checkpoint", {{1,1}}},
            {"children", {{1,1}}},
            {"chocolate", {{0,1}}},
            {"cinema", {{0,1}}},
            {"clark", {{0,1}}},
            {"clasped", {{1,1}}},
            {"classic", {{0,1}}},
            {"classics", {{0,1}}},
            {"combined", {{0,1}}},
            {"come", {{0,1}, {1,1}}},
            {"common", {{0,1}, {1,1}}},
            {"computer", {{1,1}}},
            {"consult", {{1,1}}},
            {"containing", {{1,1}}},
            {"contemporary", {{0,1}}},
            {"contributions", {{0,1}}},
            {"convictions", {{0,1}}},
            {"cooper", {{0,1}}},
            {"coppola", {{0,1}}},
            {"crowe", {{0,1}}},
            {"crown", {{1,1}}},
            {"crucial", {{0,1}}},
            {"crying", {{0,1}}},
            {"current", {{0,1}}},
            {"cusack", {{0,1}}},
            {"damon", {{0,1}}},
            {"dave", {{1,1}}},
            {"day", {{1,1}}},
            {"death", {{1,1}}},
            {"delays", {{1,1}}},
            {"desire", {{0,1}}},
            {"despite", {{0,1}}},
            {"differ", {{0,1}}},
            {"directors", {{0,2}}},
            {"disappear", {{0,1}}},
            {"distributing", {{0,1}}},
            {"does", {{1,1}}},
            {"don", {{1,1}}},
            {"done", {{0,1}}},
            {"dream", {{0,1}}},
            {"eclecticism", {{0,1}}},
            {"edward", {{0,1}}},
            {"eight", {{1,1}}},
            {"elizabeth", {{0,1}}},
            {"emotions", {{0,1}}},
            {"enjoy", {{1,1}}},
            {"entertainment", {{0,1}}},
            {"enthrall", {{0,1}}},
            {"entire", {{1,1}}},
            {"era", {{0,1}}},
            {"everything", {{1,1}}},
            {"fact", {{1,1}}},
            {"fairy", {{1,1}}},
            {"fall", {{1,1}}},
            {"federico", {{0,1}}},
            {"feelings", {{0,1}}},
            {"fellini", {{0,1}}},
            {"filmmaking", {{0,1}}},
            {"films", {{0,6}}},
            {"financed", {{0,1}}},
            {"flame", {{1,1}}},
            {"flight", {{1,1}}},
            {"floor", {{1,1}}},
            {"for", {{0,3}, {1,2}}},
            {"ford", {{0,2}}},
            {"foreign", {{0,2}}},
            {"forget", {{1,1}}},
            {"forward", {{1,1}}},
            {"frances", {{0,1}}},
            {"francis", {{0,1}}},
            {"fresh", {{0,1}}},
            {"from", {{0,2}, {1,2}}},
            {"fu", {{1,1}}},
            {"fun", {{1,1}}},
            {"gable", {{0,1}}},
            {"game", {{0,1}}},
            {"garde", {{0,1}}},
            {"gary", {{0,1}}},
            {"generation", {{0,4}}},
            {"giant", {{1,1}}},
            {"give", {{1,1}}},
            {"given", {{0,1}}},
            {"go", {{1,1}}},
            {"god", {{1,1}}},
            {"going", {{0,1}}},
            {"good", {{1,1}}},
            {"grant", {{0,1}}},
            {"great", {{0,1}}},
            {"greatest", {{0,1}}},
            {"group", {{1,1}}},
            {"guide", {{1,2}}},
            {"guns", {{1,1}}},
            {"gwyneth", {{0,1}}},
            {"had", {{0,1}}},
            {"hands", {{1,1}}},
            {"harvey", {{0,1}}},
            {"has", {{0,3}, {1,2}}},
            {"have", {{0,7}, {1,5}}},
            {"hawks", {{0,1}}},
            {"he", {{0,3}, {1,1}}},
            {"head", {{0,1}}},
            {"hearty", {{1,1}}},
            {"help", {{1,1}}},
            {"his", {{0,1}}},
            {"hitchcock", {{0,1}}},
            {"holding", {{1,1}}},
            {"hollywood", {{0,3}}},
            {"hours", {{1,1}}},
            {"how", {{0,1}, {1,2}}},
            {"howard", {{0,1}}},
            {"however", {{0,1}}},
            {"iconic", {{0,1}}},
            {"id", {{1,5}}},
            {"ids", {{1,1}}},
            {"if", {{1,3}}},
            {"ii", {{0,1}}},
            {"illustrious", {{0,1}}},
            {"impact", {{0,1}}},
            {"important", {{0,2}}},
            {"in", {{0,8}, {1,6}}},
            {"independent", {{0,1}}},
            {"influential", {{0,1}}},
            {"innovative", {{0,1}}},
            {"inside", {{0,2}}},
            {"insisting", {{1,1}}},
            {"international", {{1,1}}},
            {"intimate", {{0,1}}},
            {"into", {{0,1}}},
            {"introduced", {{0,1}}},
            {"invisible", {{1,1}}},
            {"is", {{0,6}, {1,3}}},
            {"it", {{0,1}, {1,4}}},
            {"john", {{0,3}}},
            {"joke", {{1,1}}},
            {"joking", {{1,1}}},
            {"julianne", {{0,1}}},
            {"just", {{1,1}}},
            {"karate", {{1,1}}},
            {"keep", {{1,1}}},
            {"kevin", {{0,1}}},
            {"kind", {{1,1}}},
            {"knee", {{1,1}}},
            {"knives", {{1,1}}},
            {"know", {{1,1}}},
            {"kung", {{1,1}}},
            {"language", {{0,1}}},
            {"laptop", {{1,1}}},
            {"launched", {{0,1}}},
            {"life", {{0,1}}},
            {"like", {{0,4}}},
            {"lines", {{1,1}}},
            {"link", {{0,1}}},
            {"loaded", {{1,1}}},
            {"long", {{1,1}}},
            {"loving", {{1,1}}},
            {"luggage", {{1,1}}},
            {"made", {{0,2}}},
            {"magical", {{1,1}}},
            {"manner", {{1,1}}},
            {"many", {{0,1}}},
            {"martin", {{0,1}}},
            {"matt", {{0,1}}},
            {"matter", {{0,1}}},
            {"may", {{1,5}}},
            {"mcdormand", {{0,1}}},
            {"mean", {{1,1}}},
            {"means", {{0,1}}},
            {"medium", {{1,1}}},
            {"meekly", {{1,1}}},
            {"miami", {{1,1}}},
            {"miramax", {{0,3}}},
            {"modern", {{0,1}}},
            {"money", {{0,1}}},
            {"moore", {{0,1}}},
            {"more", {{0,3}, {1,1}}},
            {"morons", {{1,1}}},
            {"most", {{0,2}}},
            {"movie", {{0,1}}},
            {"movies", {{0,7}}},
            {"moving", {{1,1}}},
            {"much", {{1,1}}},
            {"must", {{1,1}}},
            {"new", {{0,2}}},
            {"next", {{0,1}}},
            {"no", {{0,3}}},
            {"non", {{1,1}}},
            {"norton", {{0,1}}},
            {"not", {{1,5}}},
            {"nothing", {{1,1}}},
            {"objects", {{1,2}}},
            {"of", {{0,17}, {1,6}}},
            {"off", {{1,2}}},
            {"officer", {{1,1}}},
            {"on", {{0,2}, {1,7}}},
            {"one", {{0,1}, {1,4}}},
            {"only", {{0,1}}},
            {"onto", {{1,1}}},
            {"open", {{0,1}}},
            {"opens", {{1,1}}},
            {"opportunity", {{0,1}}},
            {"or", {{0,3}, {1,2}}},
            {"orson", {{0,1}}},
            {"out", {{1,1}}},
            {"outside", {{0,1}}},
            {"pacemakers", {{1,1}}},
            {"paltrow", {{0,1}}},
            {"pants", {{1,1}}},
            {"paradiso", {{0,1}}},
            {"particular", {{0,1}}},
            {"parts", {{0,1}}},
            {"pass", {{1,5}}},
            {"passes", {{1,1}}},
            {"past", {{0,2}}},
            {"pay", {{0,1}}},
            {"peanut", {{1,1}}},
            {"people", {{0,1}}},
            {"performances", {{0,1}}},
            {"person", {{1,1}}},
            {"personnel", {{1,5}}},
            {"photo", {{1,6}}},
            {"piano", {{1,2}}},
            {"pictures", {{0,1}}},
            {"pitt", {{0,1}}},
            {"plane", {{1,1}}},
            {"plastic", {{1,3}}},
            {"playing", {{0,2}}},
            {"pockets", {{1,1}}},
            {"point", {{1,1}}},
            {"possessions", {{1,1}}},
            {"postino", {{0,1}}},
            {"precisely", {{0,1}}},
            {"predecessors", {{0,1}}},
            {"presented", {{1,1}}},
            {"prevent", {{1,1}}},
            {"produce", {{0,1}}},
            {"producers", {{0,1}}},
            {"producing", {{0,1}}},
            {"production", {{1,1}}},
            {"prohibited", {{1,1}}},
            {"promise", {{0,1}}},
            {"promoting", {{0,1}}},
            {"purpose", {{0,1}}},
            {"put", {{1,4}}},
            {"ready", {{1,5}}},
            {"really", {{1,1}}},
            {"reason", {{0,1}}},
            {"recognized", {{0,1}}},
            {"relationship", {{0,1}}},
            {"reminding", {{1,1}}},
            {"remove", {{1,3}}},
            {"responsible", {{0,1}}},
            {"roles", {{0,1}}},
            {"round", {{1,1}}},
            {"russell", {{0,1}}},
            {"s", {{0,4}, {1,3}}},
            {"sake", {{1,1}}},
            {"says", {{1,1}}},
            {"scary", {{1,1}}},
            {"scorsese", {{0,1}}},
            {"security", {{1,4}}},
            {"see", {{0,1}, {1,1}}},
            {"seemed", {{0,1}}},
            {"semi", {{0,1}}},
            {"sense", {{1,1}}},
            {"seriousness", {{0,1}}},
            {"sets", {{1,1}}},
            {"sharp", {{1,1}}},
            {"shoes", {{1,1}}},
            {"shooting", {{1,1}}},
            {"shot", {{0,1}}},
            {"should", {{1,2}}},
            {"shuffle", {{1,1}}},
            {"signals", {{1,1}}},
            {"size", {{1,1}}},
            {"slapping", {{1,1}}},
            {"sleeper", {{1,1}}},
            {"small", {{1,1}}},
            {"smaller", {{0,1}}},
            {"sofa", {{1,1}}},
            {"some", {{1,2}}},
            {"sony", {{0,1}}},
            {"sort", {{0,1}}},
            {"spacey", {{0,1}}},
            {"spears", {{1,1}}},
            {"specialize", {{0,1}}},
            {"spending", {{1,1}}},
            {"spielberg", {{0,1}}},
            {"spring", {{1,1}}},
            {"stand", {{1,1}}},
            {"stars", {{0,2}}},
            {"states", {{0,1}}},
            {"stereotype", {{0,1}}},
            {"steven", {{0,1}}},
            {"still", {{0,1}}},
            {"strangling", {{1,1}}},
            {"studio", {{0,1}}},
            {"studios", {{0,2}}},
            {"successful", {{0,1}}},
            {"such", {{1,1}}},
            {"suitcase", {{1,2}}},
            {"sum", {{0,1}}},
            {"t", {{1,3}}},
            {"take", {{1,3}}},
            {"taylor", {{0,1}}},
            {"terroristic", {{1,1}}},
            {"than", {{0,1}, {1,1}}},
            {"that", {{0,2}, {1,6}}},
            {"the", {{0,25}, {1,21}}},
            {"their", {{0,4}, {1,1}}},
            {"them", {{0,1}, {1,3}}},
            {"themselves", {{0,1}}},
            {"then", {{1,1}}},
            {"there", {{1,1}}},
            {"these", {{0,2}}},
            {"they", {{0,3}, {1,1}}},
            {"this", {{0,2}, {1,1}}},
            {"those", {{0,1}}},
            {"thoughts", {{0,1}}},
            {"three", {{1,1}}},
            {"through", {{1,1}}},
            {"throughout", {{1,1}}},
            {"throwers", {{1,1}}},
            {"tightly", {{1,1}}},
            {"time", {{1,1}}},
            {"to", {{0,11}, {1,13}}},
            {"total", {{1,1}}},
            {"tough", {{1,1}}},
            {"travelling", {{1,2}}},
            {"tray", {{1,3}}},
            {"trays", {{1,1}}},
            {"try", {{1,1}}},
            {"twin", {{0,1}}},
            {"two", {{1,1}}},
            {"under", {{1,2}}},
            {"uniquely", {{0,1}}},
            {"united", {{0,1}}},
            {"unlike", {{0,1}}},
            {"unnecessary", {{1,1}}},
            {"until", {{1,2}}},
            {"up", {{0,1}, {1,1}}},
            {"use", {{1,1}}},
            {"variety", {{0,1}}},
            {"victim", {{1,1}}},
            {"vivid", {{0,1}}},
            {"waiting", {{1,1}}},
            {"wanted", {{0,1}}},
            {"wardrobe", {{1,1}}},
            {"watch", {{0,1}}},
            {"water", {{0,1}}},
            {"wayne", {{0,1}}},
            {"ways", {{0,1}}},
            {"weinstein", {{0,3}}},
            {"well", {{0,1}}},
            {"welles", {{0,1}}},
            {"whacky", {{1,1}}},
            {"what", {{0,3}}},
            {"wheels", {{1,2}}},
            {"when", {{0,1}, {1,2}}},
            {"where", {{1,1}}},
            {"wherever", {{0,1}}},
            {"which", {{1,1}}},
            {"while", {{1,1}}},
            {"who", {{0,1}, {1,1}}},
            {"will", {{0,1}}},
            {"with", {{0,2}, {1,1}}},
            {"won", {{1,1}}},
            {"works", {{0,1}}},
            {"world", {{0,1}}},
            {"worms", {{1,2}}},
            {"would", {{1,1}}},
            {"wouldn", {{1,1}}},
            {"years", {{0,2}}},
            {"you", {{1,18}}},
            {"your", {{1,14}}},
            {"youth", {{0,1}}}
    };

    return varInvertedIndex;
}

const std::vector<std::string> &Bases::filePaths()
{
    static const std::vector<std::string> varFilePaths
            {
                    "../../tests/resources/resources/file001-test.txt",
                    "../../tests/resources/resources/file002-test.txt",
                    "../../tests/resources/resources/file003-test.txt"
            };

    return varFilePaths;
}

const std::vector<std::string> &Bases::requests()
    {
        static const std::vector<std::string> varRequests
                {
                     "susic",
                     "water anothers gaad saa",
                     "of the and water is year"
                };

        return varRequests;
    }

const std::string &Bases::about()
{
    static const std::string varAbout
            {
                    R"("SkillboxSearchEngine", v."1.0.0")"
            };

    return varAbout;
}

const std::vector<std::vector<RelativeIndex>> &Bases::relativeIndex()
    {
        static const std::vector<std::vector<RelativeIndex>> varRelativeIndex
        {
                {{0,0}, {1,0}, {2,0}},
                {{0,0.017544}, {1,0}, {2,0}},
                {{0,1}, {2,0.947368}, {1,0.77193}}
        };

        return varRelativeIndex;
    }

const std::vector<std::vector<RelativeIndex>> &Bases::relativeIndex_file003_missing()
{
    static const std::vector<std::vector<RelativeIndex>> varRelativeIndex
            {
                    {{0,0}, {1,0}},
                    {{0,0.017544}, {1,0}},
                    {{0,1}, {1,0.77193}}
            };

    return varRelativeIndex;
}

const std::vector<std::vector<RelativeIndex>> &Bases::relativeIndex_3()
{
    static const std::vector<std::vector<RelativeIndex>> varRelativeIndex
            {
                    {{0,0}, {1,0}, {2,0}},
                    {{0,0.018}, {1,0}, {2,0}},
                    {{0,1}, {2,0.947}, {1,0.772}}
            };

    return varRelativeIndex;
}

const std::vector<std::vector<std::pair<std::uint64_t, float>>> &Bases::exportRelativeIndex()
{
    static const std::vector<std::vector<std::pair<std::uint64_t, float>>> varExportRelativeIndex
            {
                    {{0,0}, {1,0}, {2,0}},
                    {{0,0.017544}, {1,0}, {2,0}},
                    {{0,1}, {2,0.947368}, {1,0.77193}}
            };

    return varExportRelativeIndex;
}

const JSON &Bases::configJSON()
    {
        static const JSON varConfig= JSON::parse(R"(
    {
         "config":
         {
              "name": "SkillboxSearchEngine",
              "version": "1.0.0",
              "max_responses": 5
         },
        "files":
        [
             "../../tests/resources/resources/file001-test.txt",
             "../../tests/resources/resources/file002-test.txt",
             "../../tests/resources/resources/file003-test.txt"
        ]
    }
    )");

        return varConfig;
    }

const JSON &Bases::configNotMatchJSON()
{
    static const JSON varConfig= JSON::parse(R"(
    {
         "config":
         {
              "name": "SkillboxSearchEngine",
              "version": "1.0.0"

         },
        "files":
        [
             "../../tests/resources/resources/file001-test.txt",
             "../../tests/resources/resources/file002-test.txt",
             "../../tests/resources/resources/file003-test.txt"
        ]
    }
    )");

    return varConfig;
}

const JSON &Bases::configEmptyJSON()
{
    static const JSON varConfig= JSON::parse(R"(
    {
         "config":
         {
              "name": "SkillboxSearchEngine",
              "version": "1.0.0",
              "max_responses": 5
         },
        "files":
        [

        ]
    }
    )")["files"];

    return varConfig;
}

const JSON &Bases::requestsJSON()
    {
        static const JSON varRequests= JSON::parse(R"(
    {
         "requests":
    [
    "susic",
    "water anothers gaad saa",
    "of the and water is year"

  ]
    }
    )");

        return varRequests;
    }

const JSON &Bases::requestsEmptyJSON()
{
    static const JSON varRequests= JSON::parse(R"(
    {
         "requests":
    [


  ]
    }
    )")["requests"];

    return varRequests;
}

const JSON &Bases::jsonTest()
{
    static const JSON varRequests= JSON::parse(R"(
    {
         "requests":
    [
    "susic",
    "water anothers gaad saa",
    "of the and water is year"

  ]
    }
    )");

    return varRequests;
}

const JSON &Bases::answersJSON()
    {
        static const JSON varAnswers= JSON::parse(R"(
    {
  "answers": {
    "request001": {
      "result": "false"
    },
    "request002": {
      "result": "true",
      "docid": 0,
      "rank": 0.017544
    },
    "request003": {
      "result": "true",
      "relevance": [
        {
          "docid": 0,
          "rank": 1.0
        },
        {
          "docid": 2,
          "rank": 0.947368
        },
        {
          "docid": 1,
          "rank": 0.77193
        }
      ]
    }
  }
    }
    )");

        return varAnswers;
    }

const JSON &Bases::answersJSON_2()
{
    static const JSON varAnswers= JSON::parse(R"(
    {
  "answers": {
    "request001": {
      "result": "false"
    },
    "request002": {
      "result": "true",
      "docid": 0,
      "rank": 0.017544
    },
    "request003": {
      "result": "true",
      "relevance": [
        {
          "docid": 0,
          "rank": 1.0
        },
        {
          "docid": 2,
          "rank": 0.947368
        }
      ]
    }
  }
    }
    )");

    return varAnswers;
}

const JSON &Bases::answersJSON_3()
{
    static const JSON varAnswers= JSON::parse(R"(
    {
  "answers": {
    "request001": {
      "result": "false"
    },
    "request002": {
      "result": "true",
      "docid": 0,
      "rank": 0.018
    },
    "request003": {
      "result": "true",
      "relevance": [
        {
          "docid": 0,
          "rank": 1.0
        },
        {
          "docid": 2,
          "rank": 0.947
        },
        {
          "docid": 1,
          "rank": 0.772
        }
      ]
    }
  }
    }
    )");

    return varAnswers;
}

const JSON &Bases::answersJSON_file003_missing()
{
    static const JSON varAnswers= JSON::parse(R"(
    {
  "answers": {
    "request001": {
      "result": "false"
    },
    "request002": {
      "result": "true",
      "docid": 0,
      "rank": 0.017544
    },
    "request003": {
      "result": "true",
      "relevance": [
        {
          "docid": 0,
          "rank": 1.0
        },
        {
          "docid": 1,
          "rank": 0.77193
        }
      ]
    }
  }
    }
    )");

    return varAnswers;
}



std::string getLastFilePath()
{
    //Подготовить переменные
    std::filesystem::directory_entry directoryEntry;
    std::chrono::system_clock::time_point timePoint{};

    //Для каждого файла директории
    for (const auto& currentDirectoryEntry : std::filesystem::directory_iterator(ProgramArguments::logsFolderName()))
    {
        //Преобразовать время в нужный тип
        std::chrono::system_clock::time_point currentTimePoint{std::chrono::clock_cast<std::chrono::system_clock>(currentDirectoryEntry.last_write_time())};
        //Если время изменения текущего файла позже
        if (currentTimePoint > timePoint)
        {
            //Запомнить файл
            directoryEntry = currentDirectoryEntry;
        }
    }

    //Вернуть путь файла
    return directoryEntry.path().string();
}

std::string timePointToString(const std::chrono::system_clock::time_point& now)
{
    //Преобразовать момент времени в объект времени POSIX
    std::time_t t{std::chrono::system_clock::to_time_t(now)};

    //Задать размер строки
    std::string ts(256,0);

    //Преобразовать время в строку, и задать размер строки
    ts.resize(std::strftime(&ts[0], ts.size(), ProgramArguments::dateTimeFormat().c_str(), std::localtime(&t)));

    //Преобразовать момент времени в секунды
    std::chrono::system_clock::time_point nowSeconds{std::chrono::time_point_cast<std::chrono::seconds>(now)};

    //Получить наносекунды
    std::chrono::nanoseconds nanoseconds{now - nowSeconds};

    //Преобразовать наносекунды в строку
    std::stringstream ss4;
    ss4 << nanoseconds.count();
    std::string strNanosecondsCount;
    ss4 >> strNanosecondsCount;

    //Вернуть строку времени
    return ts + strNanosecondsCount;
}

std::string  getTimePoint()
{
    //Получить текущий момент времени
    std::chrono::system_clock::time_point now{std::chrono::system_clock::now()};

    //Отметка времени
    std::string timePoint{timePointToString(now)};

    return timePoint;
}

bool isMatchingErrorLevel(const std::string& timePoint, const std::string& strErrorLevel)
{
    //Получить путь текущего лог-файла
    std::string fileName{getLastFilePath()};

    //Прочитать лог-файл
    std::string log{kav::OperationFileAndJSON::readTextFile(fileName).first};

    //Обнулить результат операции
    bool result{};

    //Определить позицию отметки времени в лог-файле
    std::string::size_type found{log.rfind(timePoint)};

    //Если отметка присутствует
    if (found != std::string::npos)
    {
        //Определить начало строки с отметкой в лог-файле
        std::string::size_type begin{log.rfind('\n', found)};
        //Определить конец строки с отметкой в лог-файле
        std::string::size_type end{log.find('\n',found)};

        //Выделить строку сообщения с отметкой
        std::string logLine{log.substr(begin + 1, end - begin - 1)};

        //Если уровень логирования совпадает
        if (logLine.find(strErrorLevel) != std::string::npos)
        {
            //Установить результат операции
            result = true;
        }
    }

    //Возвратить результат операции
    return result;
}
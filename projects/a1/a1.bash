#!/bin/bash

candidate_list=("Popeye" "Tweety" "Homer" "Bugs Bunny" "Snoopy");
valid_candidate='0'
votes=0
file_search=$1;
start_dir=$2;
candidate=$3;

next_dir=$start_dir;
cd $start_dir;

#FUNCTIONS---------------------------------------------------------------------


#Add up votes from each files and store
#Use grep to read the files and get the vote
function read_votes()
{
        cd "$next_dir"
        if [[ -e $file_search ]] 2> /dev/null; then
		add_votes=$(grep "$candidate" $file_search | grep -o "[0-9]*");
        	let "votes=$votes+$add_votes";
        fi
}


#parse the directory recursively
function parse_dir()
{
cd $next_dir;
if [[ -n $(ls -ld */) ]] 2> /dev/null; then
        for dir in "$PWD"/*; do
                if [[ -f "$dir" ]];
                then
                        continue;
                elif [[ -d "$dir" ]];
                then
                        next_dir=$dir;
                        #call read_votes after getting dir
                        read_votes;
                        parse_dir;
                fi
        done
fi
}


#check if the candidate is in the running list
function check_candidate()
{
	IFS=$''
	for item in ${candidate_list[@]}; do
		if [[ $candidate == $item ]]
		then
			valid_candidate='1';
			break;
		fi
	done;
	IFS=$'\n'

}

# END FUNCTIONS-----------------------------------------------------------------

#echo a new line for clear output
echo -e;

#check for search file or use default
if [[ -z $file_search  ]];
then
	echo "Using default search file '.vote'";
	file_search='.votes';
else
	echo "Searching for files under the name '$file_search'";
fi

#check for start directory or use current directory
if [[ -z $start_dir ]];
then
	echo "Using $PWD as starting directory";
else
	echo "Using '$start_dir' as starting directory";
fi

#check if a candidate was requested and if they are valid
if [[ -z $candidate ]];
then
	echo "Please enter a candidate's name";
	read candidate;
	check_candidate;
	if [[ $valid_candidate == '1' ]]; then
		echo "Looking for number of votes for '$candidate'";
		parse_dir;
		echo "$candidate $votes";
	else
		echo "'$candidate' is not a valid candidate. Please try again.";
		exit 1;
	fi
else
	check_candidate;
	if [[ $valid_candidate == '1' ]]; then
		echo "Looking for number of votes for '$candidate'";
		parse_dir;
		echo "$candidate $votes";
	else
		echo "'$candidate' is not a valid candidate. Please try again.";
		exit 1;
	fi
fi

#echo a new line for clear output
echo -e;

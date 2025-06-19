j() {
    if [[ "$1" == "--update" ]]; then
        "$HOME/Desktop/Project/Jump/build/jump" --update
        return
    fi

    dest=$("$HOME/Desktop/Project/jump/build/jump" "$@")
    
    if [ -d "$dest" ]; then
        cd "$dest"
    else
        
    fi
}

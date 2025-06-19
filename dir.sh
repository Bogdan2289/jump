select dir in "${dirs[@]}"; do
    if [[ -n "$dir" ]]; then
        cd "$dir"
        break
    fi
done

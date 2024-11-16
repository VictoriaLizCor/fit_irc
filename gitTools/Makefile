dirs:
	@echo ROOT_CPP_MODULES: $(CYAN) $(ROOT_CPP_MODULES) $(E_NC)
	@echo GIT_REPO: $(GREEN) $(GIT_REPO) $(E_NC)
	@echo DIRS: $(BOLD) $(DIRS) $(E_NC)
	@for subdir in $$(find $(DIRS) -type d -name "ex0*" | sort); do \
		echo "\t"$(GRAY) $$subdir $(E_NC); \
	done;
# gAdd:
# 	@echo $(CYAN) && git add $(ROOT_CPP_MODULES)
# gCommit:
# 	@echo $(GREEN) && git commit -e ; \
# 	ret=$$? ; \
# 	if [ $$ret -ne 0 ]; then \
# 		echo $(RED) "Error in commit message"; \
# 		exit 1; \
# 	fi
# gPush:
# 	@echo $(YELLOW) && git push ; \
# 	ret=$$? ; \
# 	if [ $$ret -ne 0 ]; then \
# 		echo $(RED) "git push failed, setting upstream branch\n" $(YELLOW) && \
# 		git push --set-upstream origin $(shell git branch --show-current) || \
# 		if [ $$? -ne 0 ]; then \
# 			echo $(RED) "git push --set-upstream failed with error" $(E_NC); \
# 		fi \
# 	fi
# git: cleanAll gAdd
# 	@$(MAKE) -C . gCommit; \
# 	ret=$$?; \
# 	if [ $$ret -ne 0 ]; then \
# 		exit 1; \
# 	else \
# 		$(MAKE) -C . gPush; \
# 	fi

mlog:
	@git log -5 --pretty=format:"'%h'%m%s {%cd} %b" --date=format:'%Y-%m-%d %H:%M' | \
	pygmentize -g -O  style=$$m | cut -d'|' -f1
plog:
	@git log -5 --pretty=format:"{%cd} (%h) %m %B" --date=format:'%Y-%m-%d %H:%M' |\
	pygmentize -g -O  style=material

quick: cleanAll
	@echo $(GREEN) && git commit -am "* Update in files: "; \
	ret=$$? ; \
	if [ $$ret -ne 0 ]; then \
		exit 1; \
	else \
		$(MAKE) -C . gPush; \
	fi
#$(shell git diff --name-only --diff-filter=M | awk 'NR > 1 {print prev","} {prev=$$0} END {print $0}')"
# Avoid last commit message
soft:
	@echo $(GREEN) "\nLast 10 commits:" $(E_NC)
	@$(MAKE) plog && echo 
	@read -p "Do you want to reset the last commit? (y/n) " yn; \
	case $$yn in \
		[Yy]* ) git reset --soft HEAD~1;\
		git push origin --force-with-lease $(shell git branch --show-current) ;\
		echo $(RED) "Last commit reset" $(E_NC) ;; \
		* ) echo $(MAG) "No changes made" $(E_NC) ;; \
	esac
amend:
	@echo $(CYAN) && git commit --amend; \
	result=$$?; \
	if [ $$result -ne 0 ]; then \
		echo $(RED) "The amend commit message was not modified."; \
		exit 1; \
	else \
		echo $(YELLOW) && git push origin --force-with-lease $(shell git branch --show-current); \
		exit 0; \
	fi
template:
	@git config --local commit.template .settings/.gitmessage
pre-commit:
	cp .settings/prepare-commit-msg .git/hooks/
	chmod +x .git/hooks/prepare-commit-msg
commit-msg:
	cp .settings/commit-msg .git/hooks/
	chmod +x .git/hooks/commit-msg
post-merge:
	cp .settings/post-merge .git/hooks/
	chmod +x .git/hooks/post-merge
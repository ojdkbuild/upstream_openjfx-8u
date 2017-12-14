# Copyright (C) 2007-2013, 2015 Apple Inc.  All rights reserved.
# 3.  Neither the name of Apple Inc. ("Apple") nor the names of
        &fixSVNPatchForAdditionWithHistory
        &gitDirectory
        &gitTreeDirectory
        &isGitSVNDirectory
        &parseDiffStartLine
        &svnIdentifierForPath
        &svnInfoForPath
        &svnRepositoryRootForPath
        &svnURLForPath
        &unixPath
my $unifiedDiffStartRegEx = qr#^--- ([abc]\/)?([^\r\n]+)#;
    if (isWindows()) {
sub isGitSVNDirectory($)
    my ($directory) = @_;

    my $savedWorkingDirectory = Cwd::getcwd();
    chdir($directory);
    $isGitSVN = exitStatus($?) == 0 && $output ne "";
    chdir($savedWorkingDirectory);
    return $isGitSVN;
}

sub isGitSVN()
{
    return $isGitSVN if defined $isGitSVN;

    $isGitSVN = isGitSVNDirectory(".");
sub gitTreeDirectory()
{
    chomp(my $result = `git rev-parse --show-toplevel`);
    return $result;
}

    return "v$version" ge v1.6;
        # This is the working tree root. If WebKit is a submodule,
        # then the relevant metadata directory is somewhere else.
        return gitTreeDirectory();
sub svnInfoForPath($)
    if (isSVNDirectory($file)) {
    } elsif (isGitDirectory($file)) {
        my $command = "git svn info";
        $svnInfo = `cd $relativePath && $command`;
    return $svnInfo;
}

sub svnURLForPath($)
{
    my ($file) = @_;
    my $svnInfo = svnInfoForPath($file);

    return $1;
}

sub svnRepositoryRootForPath($)
{
    my ($file) = @_;
    my $svnInfo = svnInfoForPath($file);
    return $1;
}

sub pathRelativeToSVNRepositoryRootForPath($)
{
    my ($file) = @_;
    my $svnURL = svnURLForPath($file);
    my $svnRepositoryRoot = svnRepositoryRootForPath($file);

    $svnURL =~ s/$svnRepositoryRoot\///;
sub svnIdentifierForPath($)
{
    my ($file) = @_;
    my $path = pathRelativeToSVNRepositoryRootForPath($file);

    $path =~ /^(trunk)|tags\/([\w\.\-]*)|branches\/([\w\.\-]*).*$/m;
    return $1 || $2 || $3;
}

{
    my ($path) = @_;
    if (isWindows()) {
        $path =~ s/\//\\/g;
    } else {
        $path =~ s/\\/\//g;
    }
    return $path;
}

sub unixPath($)
# Parses an SVN or Git diff header start line.
#
# Args:
#   $line: "Index: " line or "diff --git" line
#
# Returns the path of the target file or undef if the $line is unrecognized.
sub parseDiffStartLine($)
{
    my ($line) = @_;
    return $1 if $line =~ /$svnDiffStartRegEx/;
    return parseGitDiffStartLine($line) if $line =~ /$gitDiffStartRegEx/;
}

# Parse the next Unified diff header from the given file handle, and advance
# the handle so the last line read is the first line after the header.
#
# This subroutine dies if given leading junk.
#
# Args:
#   $fileHandle: advanced so the last line read from the handle is the first
#                line of the header to parse.  This should be a line
#                beginning with "Index:".
#   $line: the line last read from $fileHandle
#
# Returns ($headerHashRef, $lastReadLine):
#   $headerHashRef: a hash reference representing a diff header, as follows--
#     indexPath: the path of the target file, which is the path found in
#                the "Index:" line.
#     isNew: the value 1 if the diff is for a new file.
#     isDeletion: the value 1 if the diff is a file deletion.
#     svnConvertedText: the header text converted to a header with the paths
#                       in some lines corrected.
#   $lastReadLine: the line last read from $fileHandle.
sub parseUnifiedDiffHeader($$)
{
    my ($fileHandle, $line) = @_;

    $_ = $line;

    my $currentPosition = tell($fileHandle);
    my $indexLine;
    my $indexPath;
    if (/$unifiedDiffStartRegEx/) {
        # Use $POSTMATCH to preserve the end-of-line character.
        my $eol = $POSTMATCH;
        
        $indexPath = $2;

        # In the case of an addition, we look at the next line for the index path
        if ($indexPath eq "/dev/null") {
            $_ = <$fileHandle>;
            if (/^\+\+\+ ([abc]\/)?([^\t\n\r]+)/) {
                $indexPath = $2;
            } else {
                die "Unrecognized unified diff format.";
            }
            $_ = $line;
        }

        $indexLine = "Index: $indexPath$eol"; # Convert to SVN format.
    } else {
        die("Could not parse leading \"---\" line: \"$line\".");
    }

    seek($fileHandle, $currentPosition, 0);

    my $isDeletion;
    my $isHeaderEnding;
    my $isNew;
    my $svnConvertedText = $indexLine;
    while (1) {
        # Temporarily strip off any end-of-line characters to simplify
        # regex matching below.
        s/([\n\r]+)$//;
        my $eol = $1;
        
        if (/^--- \/dev\/null/) {
            $isNew = 1;
        } elsif (/^\+\+\+ \/dev\/null/) {
            $isDeletion = 1;
        }
        
        if (/^(---|\+\+\+) ([abc]\/)?([^\t\n\r]+)/) {
            if ($1 eq "---") {
                my $prependText = "";
                $prependText = "new file mode 100644\n" if $isNew;
                $_ = "${prependText}index 0000000..0000000\n$1 $3";
            } else {
                $_ = "$1 $3";
                $isHeaderEnding = 1;
            }
        }
        
        $svnConvertedText .= "$_$eol"; # Also restore end-of-line characters.
        
        $currentPosition = tell($fileHandle);
        $_ = <$fileHandle>; # Not defined if end-of-file reached.
        last if (!defined($_) || /$unifiedDiffStartRegEx/ || $isHeaderEnding);
    }
    
    my %header;
    
    $header{indexPath} = $indexPath;
    $header{isDeletion} = $isDeletion if $isDeletion;
    $header{isNew} = $isNew if $isNew;
    $header{svnConvertedText} = $svnConvertedText;

    return (\%header, $_);
}

    my $isUnified;
    } elsif ($line =~ $unifiedDiffStartRegEx) {
        $isUnified = 1;
        ($header, $lastReadLine) = parseUnifiedDiffHeader($fileHandle, $line);
    $header->{isUnified} = $isUnified if $isUnified;
        if (!$headerHashRef && ($line =~ $unifiedDiffStartRegEx)) {
            $headerStartRegEx = $unifiedDiffStartRegEx;
        }

        if (/^[\r\n]+$/ || /$svnPropertyValueStartRegEx/ || /$svnPropertyStartRegEx/ || /$svnPropertyValueNoNewlineRegEx/ || /$svnDiffStartRegEx/) {
# Removes a leading Subversion header without an associated diff if one exists.
#
# This subroutine dies if the specified patch does not begin with an "Index:" line.
#
# In SVN 1.9 or newer, "svn diff" of a moved/copied file without post changes always
# emits a leading header without an associated diff:
#     Index: B.txt
#     ===================================================================
# (end of file or next header)
#
# If the same file has a property change then the patch has the form:
#     Index: B.txt
#     ===================================================================
#     Index: B.txt
#     ===================================================================
#     --- B.txt    (revision 1)
#     +++ B.txt    (working copy)
#
#     Property change on B.txt
#     ___________________________________________________________________
#     Added: svn:executable
#     ## -0,0 +1 ##
#     +*
#     \ No newline at end of property
#
# We need to apply this function to the ouput of "svn diff" for an addition with history
# to remove a duplicate header so that svn-apply can apply the resulting patch.
sub fixSVNPatchForAdditionWithHistory($)
{
    my ($patch) = @_;

    $patch =~ /(\r?\n)/;
    my $lineEnding = $1;
    my @lines = split(/$lineEnding/, $patch);

    if ($lines[0] !~ /$svnDiffStartRegEx/) {
        die("First line of SVN diff does not begin with \"Index \": \"$lines[0]\"");
    }
    if (@lines <= 2) {
        return "";
    }
    splice(@lines, 0, 2) if $lines[2] =~ /$svnDiffStartRegEx/;
    return join($lineEnding, @lines) . "\n"; # patch(1) expects an extra trailing newline.
}

    my $name = $ENV{CHANGE_LOG_NAME} || $ENV{REAL_NAME} || gitConfig("user.name");
    if (not $name and !isWindows()) {
        $name = (split /\s*,\s*/, (getpwuid $<)[6])[0];
    }
    if ($contents !~ m"\nGIT binary patch\n$gitPatchRegExp$gitPatchRegExp(\Z|-- \n)") {
        return ();